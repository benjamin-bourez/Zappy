/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageIncantation
*/

#pragma once

#include "Enums.hpp"
#include "ManageAI.hpp"

namespace Zappy::AI
{
    class ManageIncantation {
        public:
            ManageIncantation();
            ~ManageIncantation();

            bool gotEnoughStones(std::map<Ressource, int> inventory, int level);
            int gotEnoughPlayers(std::vector<std::vector<Ressource>> look, int level);
            bool lookEnoughStones(std::vector<std::vector<Ressource>> look, int level);
            Incantation canIncant(std::vector<std::vector<Ressource>> look, std::map<Ressource, int> inventory, int level, Commands lastCommand);
        protected:
        private:
            std::vector<std::map<Ressource, int>> _neededStoneLevel;
            std::vector<int> _neededPlayerLevel;
    };
}
