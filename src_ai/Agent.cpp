/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Agent
*/

#include "Agent.hpp"
#include "Enums.hpp"

namespace Zappy::AI {
    Agent::Agent(std::pair<int, int> mapSize, int connectNbr, bool verbose)
    {
        std::vector<std::pair<int, int>> otop = {std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(0, -1), std::make_pair(-1, 0)};
        uuid_t id;
        char id_str[37] = {0};

        for (int i = 0; i < 7; i++)
            _inventory[(Ressource)i] = 0;
        uuid_generate(id);
        uuid_unparse(id, id_str);
        _id = std::string(id_str);
        _vision = {};
        _level = 1;
        _position = {0, 0};
        _verbose = verbose;
        _connectNbr = connectNbr;
        _mapSize = mapSize;
        _tick_fork = 39;
        _ressources = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food", "player", "empty"};
        _commandsStr = {"Forward", "Right", "Left", "Look", "Inventory", "Broadcast ", "Connect_nbr", "Fork", "Eject", "Take ", "Set ", "Incantation", ""};
        _commandsFuncs[FORWARD] = &Agent::forward;
        _commandsFuncs[RIGHT] = &Agent::right;
        _commandsFuncs[LEFT] = &Agent::left;
        _commandsFuncs[LOOK] = &Agent::look;
        _commandsFuncs[INVENTORY] = &Agent::inventory;
        _commandsFuncs[BROADCAST] = &Agent::broadcast;
        _commandsFuncs[CONNECT_NBR] = &Agent::connectNbr;
        _commandsFuncs[FORK] = &Agent::fork;
        _commandsFuncs[EJECT] = &Agent::eject;
        _commandsFuncs[TAKE] = &Agent::take;
        _commandsFuncs[SET] = &Agent::set;
        _commandsFuncs[INCANTATION] = &Agent::incantation;
        _ressourceMap = {
            {"food", FOOD},
            {"linemate", LINEMATE},
            {"deraumere", DERAUMERE},
            {"sibur", SIBUR},
            {"mendiane", MENDIANE},
            {"phiras", PHIRAS},
            {"thystame", THYSTAME},
            {"player", PLAYER},
            {"", EMPTY}
        };
        _foodManager = std::make_shared<ManageFood>();
        _stoneManager = std::make_shared<ManageStone>();
        _incantationManager = std::make_shared<ManageIncantation>();
        _isIncantating = false;
        _orientation = otop[NORTH];
        _inventory[FOOD] = 10;
        _lastCommand = {UNKNOWN, ""};
        _lastInv = 1;
        _lastLook = 1;
        _isHungry = true;
        _bufferOfCommands = {};
        _waitForId = 0;
        _broadcastCommands = {};
        _incantation = IncantationStatus::WAITING;
        _needed_players = 0;
        _player_ready = 0;
        _follow_incantator = false;
        _sended_id = false;
        _another_incantation = false;
        _tick_other_incantation = 0;
        _waiting_for_player = false;
        _waiting_string = "";
        _following_player = false;
        _turn = false;
        if (_verbose)
            std::cout << "[Agent][" << _id << "] created" << std::endl;
        srand(time(NULL));
    }

    Agent::~Agent()
    {
        if (_verbose)
            std::cout << "[Agent][" << _id << "] died" << std::endl;
    }

    // Setter, compacted for readability purpose (fold methods)
    void Agent::setInventory(std::map<Ressource, int> inventory)
    {
        _inventory = inventory;
    }
    void Agent::setRessource(Ressource r, int nb)
    {
        _inventory[r] = nb;
    }
    void Agent::setVision(std::vector<std::vector<Ressource>> vision)
    {
        _vision = vision;
    }
    void Agent::setLevel(int level)
    {
        _level = level;
    }
    void Agent::setX(int x)
    {
        _position.first = x;
    }
    void Agent::setY(int y)
    {
        _position.second = y;
    }
    void Agent::setOrientation(int orientation)
    {
        if (orientation == NORTH)
            _orientation = std::make_pair(0, 1);
        else if (orientation == EAST)
            _orientation = std::make_pair(1, 0);
        else if (orientation == SOUTH)
            _orientation = std::make_pair(0, -1);
        else if (orientation == WEST)
            _orientation = std::make_pair(-1, 0);
    }
    void Agent::setOrientation(std::pair<int, int> orientation)
    {
        _orientation = orientation;
    }
    void Agent::setPosition(std::pair<int, int> position)
    {
        _position = position;
    }

    // Getter, compacted for readability purpose (fold methods)
    std::map<Ressource, int> Agent::getInventory() const
    {
        return _inventory;
    }
    int Agent::getRessource(Ressource r) const
    {
        return _inventory.at(r);
    }
    std::vector<std::vector<Ressource>> Agent::getVision() const
    {
        return _vision;
    }
    int Agent::getLevel() const
    {
        return _level;
    }
    int Agent::getX() const
    {
        return _position.first;
    }
    int Agent::getY() const
    {
        return _position.second;
    }
    std::pair<int, int> Agent::getPosition() const
    {
        return _position;
    }
    int Agent::getOrientation() const
    {
        if (_orientation == std::make_pair(0, 1))
            return NORTH;
        else if (_orientation == std::make_pair(1, 0))
            return EAST;
        else if (_orientation == std::make_pair(0, -1))
            return SOUTH;
        else if (_orientation == std::make_pair(-1, 0))
            return WEST;
        return -1;
    }

    std::string Agent::getId() const
    {
        return _id;
    }

    bool Agent::getHunger() const
    {
        return _isHungry;
    }

    std::string Agent::getLastCommand() const
    {
        std::string output = "";

        output += _commandsStr[_lastCommand.first];
        output += _lastCommand.second;
        return output;
    }

    // Actions

    std::string Agent::update(std::string &message)
    {
        std::cout << *this << std::endl;
        std::cout << "[Agent][" << _id << "] received \"" << message << "\" from server, updating" << std::endl;
        Incantation actionIncant;
        bool isBroadcast = message.substr(0, message.find(" ")) == "broadcast";
        int K = 0;

        if (_another_incantation) {
            _tick_other_incantation++;
            if (_tick_other_incantation >= 20) {
                _another_incantation = false;
                _tick_other_incantation = 0;
            }
        }

        manageBroadcast();
        if (message == "eject")
            return "\n";
        if (message == "Elevation underway" && _lastCommand.first != INCANTATION) {
            _waiting_for_player = false;
            _lastCommand = {INCANTATION, ""};
            _isIncantating = true;
            return "\n";
        }
        if (message.find("Current level") != std::string::npos && _lastCommand.first != INCANTATION) {
            _isIncantating = false;
            incantation(message);
            return askServer(_lastCommand.first, _lastCommand.second);
        }
        if (message == "ko" && _isIncantating == true)
            _isIncantating = false;
        if (interpretAnswer(message) == false) {
            return "\n";
        }
        if (_lastCommand.first == INCANTATION) {
            if (message == "Elevation underway") {
                _isIncantating = true;
                return askServer(INCANTATION, "");
            }
            if (message == "ko")
                return askServer(LOOK, "");
        }
        _lastInv++;
        if (_lastInv == 5) {
            _lastInv = 0;
            if (_lastCommand.first != INVENTORY) {
                _lastCommand = {INVENTORY, ""};
                return askServer(INVENTORY);
            }
        }
        if (_bufferOfCommands.size() != 0 && _inventory[FOOD] > 10 && _following_player)
            return (executeBuffer());
        _lastLook++;
        if (_lastLook >= 3 && !_following_player) {
            _lastLook = 0;
            if (_lastCommand.first != LOOK) {
                _lastCommand = {LOOK, ""};
                return askServer(LOOK);
            }
        }
        if (_bufferOfCommands.size() != 0)
            return executeBuffer();
        if (_inventory[FOOD] < 10) {
            _waiting_for_player = false;
            _following_player = false;
            _isHungry = true;
        }
        if (_inventory[FOOD] > 20)
            _isHungry = false;
        if (_isHungry) {
            _bufferOfCommands = _foodManager->getCommand(_vision, _lastCommand);
            return executeBuffer();
        }
        if (isBroadcast) {
            for (auto &s: _broadcastCommands[0].substr(_broadcastCommands[0].find(" ") + 1, _broadcastCommands[0].find(",")))
                if (!std::isdigit(s))
                    return "\n";
            K = std::stoi(_broadcastCommands[0].substr(_broadcastCommands[0].find(" ") + 1, _broadcastCommands[0].find(",")));
            std::string text = _broadcastCommands[0].substr(_broadcastCommands[0].find(",") + 1);
            if (_verbose)
                std::cout << "[Agent][" << _id << "] received broadcast: \"" << text << "\" from " << K << std::endl;
            _bufferOfCommands = _broadcast->followBroadcast(text, K, _level);
            return askServer(LOOK);
        }


        actionIncant = _incantationManager->canIncant(_vision, _inventory, _level, _lastCommand.first);

        std::cout << "\n\n\nACTION INCANT : " << actionIncant << "\n\n\n";

        if (actionIncant == SUCCESS) {
            std::cout << "success" << std::endl;
            return askServer(INCANTATION);
        } else if (actionIncant == NOTENOUGHRESSOURCES) {
            std::cout << "not enough ressources" << std::endl;
            _bufferOfCommands = _stoneManager->getCommand(_vision, _inventory, _level);
        } else if (actionIncant == NOTENOUGHFOOD) {
            std::cout << "not enough food" << std::endl;
            _isHungry = true;
        } else if (actionIncant == NOTENOUGHPLAYER && !_waiting_for_player && !_following_player && !_another_incantation) {
            std::cout << "not enough player" << std::endl;
            _bufferOfCommands.push_back(_broadcast->SendBroadcast("INCANTATE " + _id + " WANT " + std::to_string(_level)));
        } else if (actionIncant == NOTENOUGHPLAYER) {
            return askServer(BROADCAST, _waiting_string);
        } else if (actionIncant == TOOMANYPLAYER) {
            std::cout << "too many player" << std::endl;
        } else if (actionIncant == SETRESSOURCES) {
            std::cout << "set ressources" << std::endl;
            _bufferOfCommands = setAllRessources();
        }
        if (_playersId.size() + _connectNbr < 15) {
            std::cout << "fork" << std::endl;
            std::cout << "connectNbr: " << _connectNbr << std::endl;
            std::cout << "playersId: " << _playersId.size() << std::endl;
            std::cout << "tick_fork: " << _tick_fork << std::endl;
            _bufferOfCommands.push_back({FORK, ""});
        }

        return executeBuffer();
    }

    bool Agent::interpretAnswer(std::string &message)
    {
        if (_lastCommand.first != UNKNOWN) {
            return (this->*_commandsFuncs[_lastCommand.first])(message);
        }
        return true;
    }

    std::string Agent::executeBuffer()
    {
        if (_bufferOfCommands.size() != 0) {
            _lastCommand = _bufferOfCommands[0];
            if (_ressourceMap.find(_bufferOfCommands[0].second) != _ressourceMap.end())
                _lastRessource = _ressourceMap[_bufferOfCommands[0].second];
            else 
                _lastRessource = EMPTY;
            _bufferOfCommands.erase(_bufferOfCommands.begin());
            return askServer(_lastCommand.first, _lastCommand.second);
        }
        return askServer(FORWARD);
    }

    std::vector<std::pair<Commands, std::string>> Agent::setAllRessources()
    {
        std::vector<std::pair<Commands, std::string>> buffer = {};

        for (auto &ressource : _inventory) {
            if (ressource.first != FOOD) {
                for (int i = 0; i < ressource.second; i++)
                    buffer.push_back({SET, _ressources[ressource.first]});
            }
        }
        buffer.push_back({LOOK, ""});
        return buffer;
    }

    std::string Agent::askServer(Commands command, std::string message)
    {
        std::string messageToSend = "";

        _tick_fork++;
        messageToSend += _commandsStr[command];
        if (command == BROADCAST || command == TAKE || command == SET)
            messageToSend += message;
        if (_verbose)
            std::cout << "[Agent][" << _id << "] ask server: " << messageToSend << std::endl;
        if (command == INCANTATION && _lastCommand.first == INCANTATION) {
            messageToSend = "";
        }
        _lastCommand = {command, message};
        return messageToSend + "\n";
    }

    bool Agent::forward(std::string &message)
    {
        (void)message;
        _position += _orientation;
        _position.first = (_position.first + _mapSize.first) % _mapSize.first;
        _position.second = (_position.second + _mapSize.second) % _mapSize.second;
        if (_verbose)
            std::cout << "[Agent][" << _id << "] move forward" << std::endl;
        return true;
    }

    bool Agent::right(std::string &message)
    {
        std::vector<std::string> dir = {"NORTH", "EAST", "SOUTH", "WEST"};

        (void)message;
        if (_orientation == std::make_pair(0, 1))
            _orientation = std::make_pair(1, 0);
        else if (_orientation == std::make_pair(1, 0))
            _orientation = std::make_pair(0, -1);
        else if (_orientation == std::make_pair(0, -1))
            _orientation = std::make_pair(-1, 0);
        else if (_orientation == std::make_pair(-1, 0))
            _orientation = std::make_pair(0, 1);
        if (_verbose)
            std::cout << "[Agent][" << _id << "] turn right, new direction: " << dir[getOrientation()] << std::endl;
        return true;
    }

    bool Agent::left(std::string &message)
    {
        std::vector<std::string> dir = {"NORTH", "EAST", "SOUTH", "WEST"};

        (void)message;
        if (_orientation == std::make_pair(0, 1))
            _orientation = std::make_pair(-1, 0);
        else if (_orientation == std::make_pair(1, 0))
            _orientation = std::make_pair(0, 1);
        else if (_orientation == std::make_pair(0, -1))
            _orientation = std::make_pair(1, 0);
        else if (_orientation == std::make_pair(-1, 0))
            _orientation = std::make_pair(0, -1);
        if (_verbose)
            std::cout << "[Agent][" << _id << "] turn left, new direction: " << dir[getOrientation()] << std::endl;
        return true;
    }

    bool Agent::look(std::string &message)
    {
        std::string output = "";
        message = message.substr(1, message.size() - 2);
        std::regex regexDelimiter(",");
        std::sregex_token_iterator iterator(message.begin(), message.end(), regexDelimiter, -1);
        std::sregex_token_iterator endIterator;
        std::vector<std::string> substrings(iterator, endIterator);

        if (message.size() == 0)
            return false;
        _vision = {};
        regexDelimiter = std::regex(" ");
        for (auto &str : substrings) {
            iterator = std::sregex_token_iterator(str.begin(), str.end(), regexDelimiter, -1);
            std::vector<std::string> substrings2(iterator, endIterator);
            std::vector<Ressource> tmp;
            for (auto &str2 : substrings2)
                if (str2 != "")
                    tmp.push_back(_ressourceMap[str2]);
            if (tmp.size() == 0)
                _vision.push_back({EMPTY});
            else
                _vision.push_back(tmp);
        }
        if (_verbose) {
            output += "[Agent][" + _id + "] look: ";
            for (std::vector<Ressource> &it : _vision) {
                output += "[";
                for (Ressource &it2 : it)
                    output += _ressources[it2] + " ";
                output = output.substr(0, output.size() - 1);
                output += "]";
            }
        }
        return true;
    }

    bool Agent::inventory(std::string &message)
    {
        std::string output = "";
        std::regex regexDelimiter(",");
        message = message.substr(1, message.size() - 2);
        std::sregex_token_iterator iterator(message.begin(), message.end(), regexDelimiter, -1);
        std::sregex_token_iterator endIterator;
        std::vector<std::string> substrings(iterator, endIterator);

        if (message.size() == 0)
            return false;
        if (message[0] != ' ')
            substrings[0] = " " + substrings[0];
        regexDelimiter = std::regex(" ");
        for (auto &str : substrings) {
            iterator = std::sregex_token_iterator(str.begin(), str.end(), regexDelimiter, -1);
            std::vector<std::string> substrings2(iterator, endIterator);

            if (substrings2.size() < 2)
                return false;
            for (auto &s: substrings2[2])
                if (!std::isdigit(s))
                    return false;
            _inventory[_ressourceMap[substrings2[1]]] = std::stoi(substrings2[2]);;
        }
        if (_verbose) {
            output += "[Agent][" + _id + "] inventory: ";
            for (auto &it : _inventory)
                output += _ressources[it.first] + ":" + std::to_string(it.second) + " ";
            std::cout << output << std::endl;
        }
        return true;
    }

    bool Agent::broadcast(std::string &message)
    {
        (void)message;
        if (_verbose)
            std::cout << "[Agent][" << _id << "] broadcast" << std::endl;
        return true;
    }

    bool Agent::connectNbr(std::string &message)
    {
        if (!std::regex_match(message, std::regex("(\\d+)"))) {
            return false;
        }
        for (auto &s: message)
            if (!std::isdigit(s))
                return false;
        _connectNbr = std::stoi(message);
        if (_verbose)
            std::cout << "[Agent][" << _id << "] connect_nbr: " << _connectNbr << std::endl;
        return true;
    }

    bool Agent::fork(std::string &message)
    {
        (void)message;
        //TODO: fork, then reset Agent if pid == 0
        if (_verbose)
            std::cout << "[Agent][" << _id << "] fork" << std::endl;
        return true;
    }

    bool Agent::eject(std::string &message)
    {
        (void)message;
        if (_verbose)
            std::cout << "[Agent][" << _id << "] yeeted players from this tile" << std::endl;
        return true;
    }

    bool Agent::take(std::string &message)
    {
        std::string output = "";

        if (_ressources.size() - 1 > _lastRessource) {
            if (message == "ok") {
                _inventory[_lastRessource] += 1;
                output += "[Agent][" + _id + "] take: " + _ressources[_lastRessource] + " ok";
            } else if (message == "ko") {
                output += "[Agent][" + _id + "] take: " + _ressources[_lastRessource] + " ko";
            }
            else
                output += "[ERROR][Agent][" + _id + "] take: " + _ressources[_lastRessource] + " " + message;
        }
        if (_verbose)
            std::cout << output << std::endl;
        return true;
    }

    bool Agent::set(std::string &message)
    {
        std::string output = "";

        if (message == "ok") {
            _inventory[_lastRessource] -= 1;
            output += "[Agent][" + _id + "] set: " + _ressources[_lastRessource] + " ok";
        } else if (message == "ko")
            output += "[Agent][" + _id + "] set: " + _ressources[_lastRessource] + " ko";
        else
            output += "[ERROR][Agent][" + _id + "] set: " + _ressources[_lastRessource] + " " + message;

        if (_verbose)
            std::cout << output << std::endl;
        return true;
    }

    bool Agent::incantation(std::string &message)
    {
        std::string output = "[Agent][" + _id + "] incantation ";

        std::cout << "INCANTATION RECEIVED: " << message << std::endl;
        if (message == "Elevation underway") {
            _lastCommand = {INCANTATION, ""};
            output += "UNDERWAY";
        } else if (message.find("Current level") != std::string::npos) {
            _level++;
            output += "FINISHED";
        } else if (message == "ko") {
            output += "KO";
        } else {
            output += "ERROR";
        }
        if (_verbose)
            std::cout << "[Agent][" << _id << "] incantation" << std::endl;
        _incanterId.clear();
        return true;
    }

    void Agent::addBroadcastCommand(std::string &message)
    {
        _broadcastCommands.push_back(message);
    }

    bool Agent::popBroadcastCommand(void)
    {
        if (_broadcastCommands.size() > 0) {
            _broadcastCommands.erase(_broadcastCommands.begin());
            return true;
        }
        return false;
    }

    bool Agent::manageBroadcast(void)
    {
        if (!_sended_id)
            sendId();
        if (_broadcastCommands.size() > 0) {
            if (_verbose)
                std::cout << "[Agent][" << _id << "] " << _broadcastCommands[0] << std::endl;
            std::string broadcast = _broadcastCommands[0].substr(11);
            broadcastCommands(broadcast);
            popBroadcastCommand();
            return true;
        }
        std::cout << "tick_fork: " << _tick_fork << std::endl;
        if (_tick_fork >= 40) {
            _tick_fork = 0;
            askId();
        }
        return false;
    }

    void Agent::broadcastCommands(std::string &message)
    {
        if (!responseToIncantate(message))
            receiveIncantate(message);
        receiveId(message);
    }

    void Agent::sendId()
    {
        _bufferOfCommands.push_back(_broadcast->SendBroadcast("ID " + _id));
        if (_verbose)
            std::cout << "[Agent][" << _id << "] sended is ID to another AI." << std::endl;
        _sended_id = true;
    }

    bool Agent::responseToIncantate(std::string broadcast)
    {
        std::string incanterId = "";
        UtilsAI utils;
        std::string str = "";

        if (std::regex_match(broadcast, std::regex("(INCANTATE\\s[\\w-]+\\sWANT\\s\\d)"))) {
            for (auto &s: broadcast.substr(broadcast.find_last_of(' ') + 1, 1))
                if (!std::isdigit(s))
                    return false;
            if (_level == std::stoi(broadcast.substr(broadcast.find_last_of(' ') + 1, 1))) {
                _another_incantation = true;
                _tick_other_incantation = 0;
                incanterId = broadcast.substr(broadcast.find_first_of(' ') + 1);
                incanterId = incanterId.substr(0, incanterId.find_first_of(' '));
                _bufferOfCommands.push_back(_broadcast->SendBroadcast("INCANTATE " + incanterId + " " + _id));
                if (_verbose)
                    std::cout << "[Agent][" << _id << "] sended INCANTATE " << incanterId << " " << _id << std::endl;
                return true;
            }
        }
        str = broadcast.substr(0, broadcast.find("WAIT") + 4);
        if (std::regex_match(str, std::regex("(INCANTATE\\s[\\w-]+\\sWAIT)"))) {
            if (broadcast.find(_id) != std::string::npos) {
                std::cout << "\n\n\nFIND WAIT INCANTATION\nPOSITION :" << _broadcastCommands[0][8] << "\n\n";
                _another_incantation = true;
                _following_player = true;
                _tick_other_incantation = 0;
                if (_turn)
                    _bufferOfCommands = {utils.goToPlayer(_broadcastCommands[0][8] - 48)};
                else
                    _bufferOfCommands = {std::make_pair(LOOK, "")};
                _turn = !_turn;
                return true;
            } else if (_broadcastCommands[0][8] == '0') {
                _bufferOfCommands = {std::make_pair(FORWARD, "")};
                std::cout << "NOT TAKING STONES BECAUSE OF INCANTATION" << std::endl;
                return true;
            }
        }
        return false;
    }

    void Agent::receiveIncantate(std::string broadcast)
    {
        static const std::vector<std::size_t> neededPlayers = {1, 2, 2, 4, 4, 6, 6};


        std::cout << "RECEIVE INCANTATE BROADCAST: " << broadcast << std::endl;
        if (std::regex_match(broadcast, std::regex("(INCANTATE\\s[\\w-]+\\s[\\w-]+)"))) {
            std::cout << "RECEIVED IDSSS\n\n\n";
            if (broadcast.find(_id) != std::string::npos) {
                broadcast = broadcast.substr(broadcast.find_first_of(' ') + 1);
                broadcast = broadcast.substr(broadcast.find_first_of(' ') + 1);
                _incanterId.push_back(broadcast.substr(broadcast.find_first_of(' ') + 1, 36));
                if (_incanterId.size() == neededPlayers[_level - 1] - 1) {
                    std::string str = "INCANTATE " + _id + " WAIT";
                    for (auto &it : _incanterId)
                        str += " " + it;
                    _waiting_for_player = true;
                    _waiting_string = str;
                    _bufferOfCommands.push_back(_broadcast->SendBroadcast(str));
                }
            }
        }
    }

    void Agent::receiveId(std::string broadcast)
    {
        if (std::regex_match(broadcast, std::regex("(ID\\s[\\w-]+)"))) {
            broadcast = broadcast.substr(broadcast.find_first_of(' ') + 1);
            if (std::find(_playersId.begin(), _playersId.end(), broadcast) == _playersId.end())
                _playersId.push_back(broadcast);
        } else if (std::regex_match(broadcast, std::regex("(ID\\s[\\w-]+\\s\\?)"))) {
            _tick_fork = 0;
            broadcast = broadcast.substr(broadcast.find_first_of(' ') + 1, 36);
            if (std::find(_playersId.begin(), _playersId.end(), broadcast) == _playersId.end())
                _playersId.push_back(broadcast);
            _bufferOfCommands.push_back(_broadcast->SendBroadcast("ID " + _id));
        }
    }

    void Agent::askId(void)
    {
        _bufferOfCommands.push_back(_broadcast->SendBroadcast("ID " + _id + " ?"));
        _bufferOfCommands.push_back({CONNECT_NBR, ""});
    }
}

std::ostream &operator<<(std::ostream &os, const Zappy::AI::Agent &agent)
{
    std::string output = "[Agent][" + agent.getId() + "]\n";
    std::vector<std::string> ressources = {"LINEMATE", "DERAUMERE", "SIBUR", "MENDIANE", "PHIRAS", "THYSTAME", "FOOD", "PLAYER", "EMPTY"};
    std::vector<std::string> directions = {"NORTH", "EAST", "SOUTH", "WEST"};

    output += "|  Inventory: ";
    for (auto &it : agent.getInventory())
        output += ressources[it.first] + ":" + std::to_string(it.second) + " ";
    output += "\n|  Vision: ";
    for (std::vector<Zappy::AI::Ressource> &it : agent.getVision()) {
        output += "[";
        for (Zappy::AI::Ressource &it2 : it)
            output += ressources[it2] + " ";
        output = output.substr(0, output.size() - 1);
        output += "]";
    }
    output += "\n|  Level: " + std::to_string(agent.getLevel()) + "\n";
    output += "|  Position: " + std::to_string(agent.getX()) + " " + std::to_string(agent.getY()) + "\n";
    output += "|  Orientation: " + directions[agent.getOrientation()] + "\n";
    output += "|  isHungry: ";
    if (agent.getHunger())
        output += "true\n";
    else
        output += "false\n";
    output += "|  lastCommand: " + agent.getLastCommand() + "\n";
    os << output;
    return os;
}

void operator+=(std::pair<int, int> &a, std::pair<int, int> &b)
{
    a.first += b.first;
    a.second += b.second;
}