/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageStone
*/

#pragma once

#include "Enums.hpp"
#include "ManageAI.hpp"

namespace Zappy::AI {
    class ManageStone {
        public:
            ManageStone();
            ~ManageStone() = default;
            std::vector<std::pair<Commands, std::string>> getCommand(std::vector<std::vector<Ressource>> look, std::map<Ressource, int> inventory, int level);
        protected:
        private:
            std::vector<std::map<Ressource, int>> _neededStoneLevel;
            std::vector<int> _neededPlayerLevel;
            std::map<Ressource, double> _stonePriority;
            std::vector<std::string> _stoneNames;
    };
};
