/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Broadcast
*/

#pragma once

#include "Enums.hpp"
#include "ManageAI.hpp"
#include "UtilsAI.hpp"

namespace Zappy::AI {
    class Broadcast {
        public:
            Broadcast();
            ~Broadcast() = default;
            std::pair<Commands, std::string> SendBroadcast(std::string message);
            std::vector<std::pair<Commands, std::string>> followBroadcast(std::string message, int direction, int level);
        protected:
        private:
            std::vector<Commands> _commands;
    };
};
