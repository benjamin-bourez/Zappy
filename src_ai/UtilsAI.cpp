/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** UtilsAI
*/

#include "UtilsAI.hpp"

namespace Zappy::AI {
    UtilsAI::UtilsAI()
    {
        for (int i = 0; i <= 8; i++) {
            for (int j = 0; j < i * 2 + 1; j++) {
                _look_coords.push_back({j - i, i});
            }
        }

        _neededStoneLevel = {
            {{LINEMATE, 1}, {DERAUMERE, 0}, {SIBUR, 0}, {MENDIANE, 0}, {PHIRAS, 0}, {THYSTAME, 0}},
            {{LINEMATE, 1}, {DERAUMERE, 1}, {SIBUR, 1}, {MENDIANE, 0}, {PHIRAS, 0}, {THYSTAME, 0}},
            {{LINEMATE, 2}, {DERAUMERE, 0}, {SIBUR, 1}, {MENDIANE, 0}, {PHIRAS, 2}, {THYSTAME, 0}},
            {{LINEMATE, 1}, {DERAUMERE, 1}, {SIBUR, 2}, {MENDIANE, 0}, {PHIRAS, 1}, {THYSTAME, 0}},
            {{LINEMATE, 1}, {DERAUMERE, 2}, {SIBUR, 1}, {MENDIANE, 3}, {PHIRAS, 0}, {THYSTAME, 0}},
            {{LINEMATE, 1}, {DERAUMERE, 2}, {SIBUR, 3}, {MENDIANE, 0}, {PHIRAS, 1}, {THYSTAME, 0}},
            {{LINEMATE, 2}, {DERAUMERE, 2}, {SIBUR, 2}, {MENDIANE, 2}, {PHIRAS, 2}, {THYSTAME, 1}},
            {{LINEMATE, 10000}, {DERAUMERE, 10000}, {SIBUR, 10000}, {MENDIANE, 10000}, {PHIRAS, 10000}, {THYSTAME, 10000}}
        };
    }

    std::vector<std::map<Ressource, int>> UtilsAI::getNeededStoneLevel() const
    {
        return _neededStoneLevel;
    }

    std::vector<std::pair<int, int>> UtilsAI::getLookCoords() const
    {
        return _look_coords;
    }

    std::vector<std::pair<Commands, std::string>> UtilsAI::goToCase(int relative_target)
    {
        std::pair<int, int> goal = {0, 0};
        std::vector<std::pair<Commands, std::string>> commands = {};

        if (relative_target == 0)
            return commands;
        goal = _look_coords[relative_target];
        for (int j = 0; j < goal.second; j++) {
            commands.push_back({FORWARD, ""});
        }
        if (goal.first < 0) {
            commands.push_back({LEFT, ""});
            for (int i = 0; i < -goal.first; i++) {
                commands.push_back({FORWARD, ""});
            }
        } else {
            commands.push_back({RIGHT, ""});
            for (int i = 0; i < goal.first; i++) {
                commands.push_back({FORWARD, ""});
            }
        }
        return commands;
    }

   std::pair<Commands, std::string> UtilsAI::goToPlayer(int k)
    {
        if (k == 1 || k == 2 || k == 8)
            return {FORWARD, ""};
        if (k == 3 || k == 4 || k == 5)
            return {LEFT, ""};
        if (k == 6 || k == 7)
            return {RIGHT, ""};
        return {UNKNOWN, ""};
    }
};