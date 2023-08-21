/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageFood
*/

#pragma once

#include "Enums.hpp"
#include "ManageAI.hpp"

namespace Zappy::AI {
    class ManageFood {
        public:
            ManageFood() = default;
            ~ManageFood() = default;
            std::vector<std::pair<Commands, std::string>> getCommand(std::vector<std::vector<Ressource>> look, std::pair<Commands, std::string> last_command);
        protected:
        private:
    };
};
