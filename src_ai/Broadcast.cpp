/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Broadcast
*/

#include "Broadcast.hpp"

namespace Zappy::AI {

    Broadcast::Broadcast() {
        _commands = {FORWARD, FORWARD, LEFT, LEFT, LEFT, RIGHT, RIGHT, FORWARD};
    }

    std::pair<Commands, std::string> Broadcast::SendBroadcast(std::string message)
    {
        std::pair<Commands, std::string> command;
        command.first = BROADCAST;
        command.second = message;
        return command;
    }

    std::vector<std::pair<Commands, std::string>> Broadcast::followBroadcast(std::string message, int direction, int level)
    {
        std::vector<std::pair<Commands, std::string>> commands = {};
        std::string command = message.substr(0, message.find(' '));
        if (message.find("INCANTATION") == std::string::npos) {
            std::cout << "follow" << std::endl;
            int needed_lvl = std::stoi(message.substr(message.find(' ') + 1));
            if (command == "BROADCAST" && needed_lvl - 1 == level) {
                commands.push_back(std::make_pair(_commands[direction - 1], ""));
            }
        }
        return commands;
    }
};
