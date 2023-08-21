/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** UtilsAI
*/

#pragma once

#include "Enums.hpp"
#include "ManageAI.hpp"

namespace Zappy::AI {
    class UtilsAI {
        public:
            UtilsAI();
            ~UtilsAI() = default;
            std::vector<std::pair<int, int>> getLookCoords() const;
            std::vector<std::pair<Commands, std::string>> goToCase(int relative_target);
            std::pair<Commands, std::string> goToPlayer(int k);
            std::vector<std::map<Ressource, int>> getNeededStoneLevel() const;
        protected:
        private:
            std::vector<std::pair<int, int>> _look_coords;
            std::vector<std::map<Ressource, int>> _neededStoneLevel;
    };
};
