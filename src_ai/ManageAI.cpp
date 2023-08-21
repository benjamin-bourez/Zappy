/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageAI
*/

#include "ManageAI.hpp"

namespace Zappy::AI {
    ManageAI::ManageAI(int port, std::string team_name, std::string ip)
    {
        _port = port;
        _team_name = team_name;
        _ip = ip;
        _commandHandlers["WE"] = &ManageAI::processCommandWelcome;
        _commandHandlers["CL"] = &ManageAI::processCommandClientNum;
        _commandHandlers["xy"] = &ManageAI::processCommandXY;
        _commandHandlers["de"] = &ManageAI::processCommandDead;
        _canSend = false;
        _dead = false;
        _time_unit = 0;
    }

    ManageAI::~ManageAI()
    {

    }

    int ManageAI::runClient(std::shared_ptr<Zappy::Client> client)
    {
        _client = client;
        std::string command;
        std::string response;
        std::string ia_command;
        std::vector<std::string> command_list;

        if (client->connectToServer() == 84)
            return 84;
        std::cout << "Connected to server" << std::endl;
        while (signalMemory(0, 0) == 0 && _dead == false) {
            if (signalMemory(0, 0) == 1)
                break;
            if (client->receiveFromServer() == 84)
                break;
            command = client->getCommand();
            if (command != "") {
                if (command.find("message") != std::string::npos)
                    _agent->addBroadcastCommand(command);
                else
                    command_list.push_back(command);
            }
            if (_canSend && command_list.size() > 0) {
                if (command_list[0] == "dead") {
                    std::cout << "I'm dead -> level: " << _agent->getLevel() << std::endl;
                    _dead = true;
                    continue;
                }
                ia_command = _agent->update(command_list[0]);
                _agent->popBroadcastCommand();
                command_list.erase(command_list.begin());
                if (ia_command != "\n") {
                    std::cout << "[Agent] ask server: " << ia_command << "|" << std::endl;
                    client->sendToServer(ia_command);
                }
            } else if (command_list.size() > 0) {
                verifyMatching(command_list[0]);
                if (command_list[0].size() > 2 && _commandHandlers.find(command_list[0].substr(0, 2)) != _commandHandlers.end()) {
                    response = (this->*_commandHandlers[command_list[0].substr(0, 2)])(command_list[0]);
                    if (response != "\n") {
                        std::cout << "[Agent] ask server: " << response << "|" << std::endl;
                        client->sendToServer(response);
                    }
                }
                command_list.erase(command_list.begin());
                if (_canSend) {
                    std::string temp_command = "";
                    ia_command = _agent->update(temp_command);
                    _agent->popBroadcastCommand();
                    if (ia_command != "\n") {
                        std::cout << "[Agent] ask server: " << ia_command << "|" << std::endl;
                        client->sendToServer(ia_command);
                    }
                }
            }
        }
        client->closeSocket();
        return 0;
    }

    void ManageAI::verifyMatching(const std::string command)
    {
        verifyMatchingXY(command);
        verifyMatchingCL(command);
        verifyMatchingDE(command);
    }

    void ManageAI::verifyMatchingXY(const std::string &command)
    {
        std::cout << "Command XY : " << command << std::endl;
        if (std::regex_match(command, std::regex("(\\d+\\s\\d+)"))) {
            (this->*_commandHandlers["xy"])(command);
            _canSend = true;
            _agent = std::make_unique<Agent>(std::pair<int, int>(_x, _y), _unusedSlots, false);
        }
    }

    void ManageAI::verifyMatchingCL(const std::string &command)
    {
        if (std::regex_match(command, std::regex("(\\d+)"))) {
            (this->*_commandHandlers["CL"])(command);
        }
    }

    void ManageAI::verifyMatchingDE(const std::string &command)
    {
        if (command == "dead") {
            (this->*_commandHandlers["de"])(command);
        }
    }

    void ManageAI::verifyMatchingWE(const std::string &command)
    {
        if (command == "WELCOME") {
            (this->*_commandHandlers["WE"])(command);
        }
    }

    std::string ManageAI::processCommandWelcome(const std::string& command)
    {
        if (command == "WELCOME") {
            return _team_name + "\n";
        }
        return "";
    }
    
    std::string ManageAI::processCommandXY(const std::string& command)
    {
        std::string cmd = command;
        std::stringstream ss(cmd);
        std::string token;
        int i = 0;

        while (std::getline(ss, token, ' ')) {
            if (i == 0)
                _x = std::stoi(token);
            else if (i == 1)
                _y = std::stoi(token);
            i++;
        }
        return "";
    }

    std::string ManageAI::processCommandDead(const std::string& command)
    {
        if (command == "dead") {
            _dead = true;
            return _team_name + "\n";
        }
        return "";
    }

    std::string ManageAI::processCommandClientNum(const std::string& command)
    {
        _unusedSlots = std::stoi(command);
        return "";
    }
}

