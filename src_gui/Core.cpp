/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Core
*/

#include "Core.hpp"

using namespace Zappy::GUI;

Core::Core()
{
    _handlers["WEL"] = &Core::welcome;
    _handlers["msz"] = &Core::mapSize;
    _handlers["bct"] = &Core::tileContent;
    _handlers["tna"] = &Core::teamName;
    _handlers["ppo"] = &Core::playerPosition;
    _handlers["plv"] = &Core::playerLevel;
    _handlers["pin"] = &Core::playerInventory;
    _handlers["sgt"] = &Core::timeUnit;
    _handlers["sst"] = &Core::timeUnit;
    _handlers["pnw"] = &Core::playerConnection;
    _handlers["pex"] = &Core::expulse;
    _handlers["pbc"] = &Core::broadcast;
    _handlers["pic"] = &Core::incantationStart;
    _handlers["pie"] = &Core::incantationEnd;
    _handlers["pfk"] = &Core::eggLaying;
    _handlers["pdr"] = &Core::resourceDrop;
    _handlers["pgt"] = &Core::resourceCollect;
    _handlers["pdi"] = &Core::playerDeath;
    _handlers["enw"] = &Core::eggLaid;
    _handlers["ebo"] = &Core::eggConnection;
    _handlers["edi"] = &Core::eggDeath;
    _handlers["seg"] = &Core::endGame;
    _handlers["smg"] = &Core::serverMessage;
    _handlers["suc"] = &Core::unknownCommand;
    _handlers["sbp"] = &Core::commandParameter;
    _voxelInit = false;
    _lastUpdate = std::chrono::system_clock::now();
    _timeUnit = 100;
}

Core::~Core()
{
}

void Core::run()
{
    static int stop = 0;
    static int tmp = 0;

    while (signalMemory(0, 0) == 0 and stop == 0) {
        if (signalMemory(0, 0) == 1 or _client->receiveFromServer() == 84 or !_voxel.shouldStop())
            stop = 1;
        if (_voxel.shouldStart())
            break;
        std::string command = _client->getCommand();
        if (command != "")
            std::cout << "Received: " << command << std::endl;
        if (command.size() >= 3 && _handlers.find(command.substr(0, 3)) != _handlers.end())
            (this->*_handlers[command.substr(0, 3)])(command);
        tmp = _voxel.mainMenu();
        if (tmp == 2) {
            stop = 1;
            break;
        } else if (tmp == 1) {
            _voxel.updateVolume();
            if (_voxel.getTimeUnit() != _timeUnit) {
                _timeUnit = _voxel.getTimeUnit();
                _client->sendToServer("sst " + std::to_string(_timeUnit) + "\n");
            }
        }
        if (!_voxelInit)
            continue;
        _voxel.updateAudio();
    }
    _voxel.resetPosition();
    while (signalMemory(0, 0) == 0 and stop == 0) {
        if (signalMemory(0, 0) == 1 or !_voxel.shouldStop())
            break;
        if (_client->receiveFromServer() == 84)
            break;
        std::string command = _client->getCommand();
        if (command != "")
            std::cout << "Received: " << command << std::endl;
        if (command.size() >= 3 && _handlers.find(command.substr(0, 3)) != _handlers.end())
            (this->*_handlers[command.substr(0, 3)])(command);
        if (!_voxelInit)
            continue;
        _voxel.draw();
        _voxel.updateAudio();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - _lastUpdate).count() < 1000)
            continue;
        for (auto &playerID : _playerIDs) {
            _client->sendToServer("ppo " + std::to_string(playerID) + "\n");
        }
        _lastUpdate = std::chrono::system_clock::now();
    }
    _client->closeSocket();
    _voxel.unloadModels();
    _voxel.closeWindow();
}

void Core::setArgs(std::shared_ptr<Args> args)
{
    _args = args;
    _voxel.setMute(args->getMute());
}

void Core::setClient(std::shared_ptr<Client> client)
{
    _client = client;
}

void Core::welcome(std::string command)
{
    if (command == "WELCOME")
        _client->sendToServer("GRAPHIC\n");
}

void Core::mapSize(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string x = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string y = command.substr(0, command.find("\n"));

    _voxel.setMapSize(std::stoi(x), std::stoi(y));
}

void Core::tileContent(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string xStr = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string yStr = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string content = command.substr(0, command.size());
    std::vector<int> tileContent = std::vector<int>();
    int x = 0;
    int y = 0;

    for (auto &s: xStr)
        if (!std::isdigit(s))
            return;
    for (auto &s: yStr)
        if (!std::isdigit(s))
            return;
    x = std::stoi(xStr);
    y = std::stoi(yStr);
    for (int i = 0; i < 7; i++) {
        std::string quantity = content.substr(0, content.find(" "));
        for (auto &s: quantity)
            if (!std::isdigit(s))
                return;
        tileContent.push_back(std::stoi(quantity));
        content = content.substr(content.find(" ") + 1, content.size() - content.find(" ") - 1);
    }
    _voxel.setTileContent(x, y, tileContent);
}

void Core::teamName(std::string command)
{
    std::string team = command.substr(4, command.size());

    _voxel.addTeamName(team);
}

void Core::playerPosition(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string id = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string x = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string y = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string orientation = command.substr(0, command.find("\n"));

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
    for (auto &s: x)
        if (!std::isdigit(s))
            return;
    for (auto &s: y)
        if (!std::isdigit(s))
            return;
    for (auto &s: orientation)
        if (!std::isdigit(s))
            return;
    _voxel.setPlayerPosition(std::stoi(id), std::stoi(x), std::stoi(y), std::stoi(orientation));
    if (std::find(_playerIDs.begin(), _playerIDs.end(), std::stoi(id)) == _playerIDs.end()) {
        _playerIDs.push_back(std::stoi(id));
    }
}

void Core::playerLevel(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string id = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string level = command.substr(0, command.find("\n"));

    for (auto _id : _playerIDs)
        if (_id == std::stoi(id))
            _voxel.setPlayerLevel(std::stoi(id), std::stoi(level));
    _client->sendToServer("ppo " + id + "\n");
}

void Core::playerInventory(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string idString = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string content = command.substr(0, command.find("\n"));
    int id = 0;
    std::vector<int> inventory = std::vector<int>();

    for (auto &s: idString)
        if (!std::isdigit(s))
            return;
    id = std::stoi(idString);
    content = content.substr(content.find(" ") + 1, content.size() - content.find(" ") - 1);
    content = content.substr(content.find(" ") + 1, content.size() - content.find(" ") - 1);
    content = content.substr(content.find(" ") + 1, content.size() - content.find(" ") - 1);
    for (int i = 0; i < 7; ++i) {
        inventory.push_back(std::stoi(content.substr(0, content.find(" "))));
        content = content.substr(content.find(" ") + 1, content.size() - content.find(" ") - 1);
    }
    for (auto _id : _playerIDs)
        if (_id == id) {
            _voxel.setPlayerInventory(id, inventory);
            return;
        }
    _client->sendToServer("ppo " + std::to_string(id) + "\n");
    _client->sendToServer("pin " + std::to_string(id) + "\n");
}

void Core::timeUnit(std::string command)
{
    std::string time = command.substr(4, command.size());

    for (auto &s: time)
        if (!std::isdigit(s))
            return;
    _voxel.setTimeUnit(std::stoi(time));
    _timeUnit = std::stoi(time);
    _voxelInit = true;
}

void Core::playerConnection(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string id = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string x = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string y = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string orientation = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string level = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string team = command.substr(0, command.find("\n"));

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
    for (auto &s: x)
        if (!std::isdigit(s))
            return;
    for (auto &s: y)
        if (!std::isdigit(s))
            return;
    for (auto &s: orientation)
        if (!std::isdigit(s))
            return;
    _voxel.setPlayerPosition(std::stoi(id), std::stoi(x), std::stoi(y), std::stoi(orientation));
    _voxel.setPlayerLevel(std::stoi(id), std::stoi(level));
    _voxel.setPlayerTeam(std::stoi(id), team);
    _playerIDs.push_back(std::stoi(id));
}

void Core::expulse(std::string command)
{
    std::string id = command.substr(4, command.find("\n") - 4);

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
    _voxel.expulse(std::stoi(id));
}

void Core::broadcast(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string id = command.substr(0, command.find(" "));

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
    _voxel.setPlayerBroadcast(std::stoi(id));
}

void Core::incantationStart(std::string command)
{
    command = command.substr(4, command.find("\n"));
    std::string x = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size());
    std::string y = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size());
    std::string level = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size());
    std::vector<std::string> playersId;

    for (auto &s: x)
        if (!std::isdigit(s))
            return;
    for (auto &s: y)
        if (!std::isdigit(s))
            return;
    for (auto &s: level)
        if (!std::isdigit(s))
            return;
    while (command.size() > 0) {
        playersId.push_back(command.substr(0, command.find(" ")));
        if (command.find(" ") == std::string::npos)
            break;
        command = command.substr(command.find(" ") + 1, command.size());
    }
    for (auto &id : playersId)
        for (auto &s: id)
            if (!std::isdigit(s))
                return;
    _voxel.incantationStart(playersId);
}

void Core::incantationEnd(std::string command)
{
    command = command.substr(4, command.find("\n"));
    std::string x = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size());
    std::string y = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size());
    std::string result = command.substr(0, command.find("\n"));

    for (auto &s: x)
        if (!std::isdigit(s))
            return;
    for (auto &s: y)
        if (!std::isdigit(s))
            return;
    if (!std::isdigit(result.back()))
        return;
    _voxel.incantationEnd(std::stoi(x), std::stoi(y));
    _voxel.setLevelUp(true);
}

void Core::eggLaying(std::string command)
{
    std::string id = command.substr(4, command.size());

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
}

void Core::resourceDrop(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string id = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string resource = command.substr(0, command.find("\n"));

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
    for (auto &s: resource)
        if (!std::isdigit(s))
            return;
    for (auto &_id : _playerIDs)
        if (_id == std::stoi(id)) {
            _voxel.resourceDrop(std::stoi(id), std::stoi(resource));
            return;
        }
    _client->sendToServer("ppo " + id + "\n");
}

void Core::resourceCollect(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string id = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string resource = command.substr(0, command.find("\n"));

    for (auto &s: id)
        if (!std::isdigit(s))
            return;
    for (auto &s: resource)
        if (!std::isdigit(s))
            return;
    for (auto &_id : _playerIDs)
        if (_id == std::stoi(id)) {
            _voxel.resourceCollect(std::stoi(id), std::stoi(resource));
            return;
        }
    _client->sendToServer("ppo " + id + "\n");
}

void Core::playerDeath(std::string command)
{
    std::string id = command.substr(4, command.size());
    int idx = 0;

    for (auto &s: id)
        if (!std::isdigit(s)) {
            return;
        }
    for (auto &_id : _playerIDs) {
        if (_id == std::stoi(id)) {
            _voxel.playerDeath(std::stoi(id));
            _playerIDs.erase(_playerIDs.begin() + idx);
        }
        idx++;
    }
}

void Core::eggLaid(std::string command)
{
    command = command.substr(4, command.size() - 4);
    std::string eggId = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string playerId = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string x = command.substr(0, command.find(" "));
    command = command.substr(command.find(" ") + 1, command.size() - command.find(" ") - 1);
    std::string y = command.substr(0, command.find(" "));

    for (auto &s: eggId)
        if (!std::isdigit(s))
            return;
    for (auto &s: playerId)
        if (!std::isdigit(s) and s != '-')
            return;
    for (auto &s: x)
        if (!std::isdigit(s))
            return;
    for (auto &s: y)
        if (!std::isdigit(s))
            return;
    _voxel.addEgg(std::stoi(x), std::stoi(y), std::stoi(playerId), std::stoi(eggId));
}

void Core::eggConnection(std::string command)
{
    std::string eggId = command.substr(4, command.size());

    for (auto &s: eggId)
        if (!std::isdigit(s))
            return;
    _voxel.eggConnection(std::stoi(eggId));
    _playerIDs.push_back(std::stoi(eggId));
}

void Core::eggDeath(std::string command)
{
    std::string eggId = command.substr(4, command.size());

    for (auto &s: eggId)
        if (!std::isdigit(s))
            return;
    _voxel.removeEgg(std::stoi(eggId));
}

void Core::endGame(std::string command)
{
    std::string winner = command.substr(4, command.size());

    _voxel.endGame(winner);
}

void Core::serverMessage(std::string command)
{
    std::string message = command.substr(4, command.size());

    (void)message;
}

void Core::unknownCommand(std::string command)
{
    (void)command;
}

void Core::commandParameter(std::string command)
{
    (void)command;
}

void Core::unloadUponServerMissing()
{
    _voxel.unloadModels();
}
