/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageStone
*/

#include "ManageStone.hpp"

namespace Zappy::AI
{
    ManageStone::ManageStone()
    {
        _neededStoneLevel =  UtilsAI().getNeededStoneLevel();
        _neededPlayerLevel = {1, 2, 2, 4, 4, 6, 6};
        _stonePriority = {
            {LINEMATE,  0.70},
            {DERAUMERE, 0.85},
            {SIBUR,     0.90},
            {MENDIANE,  0.90},
            {PHIRAS,    0.92},
            {THYSTAME,  0.95}
        };
        _stoneNames = {"linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    }

    std::vector<std::pair<Commands, std::string>> ManageStone::getCommand(std::vector<std::vector<Ressource>> look, std::map<Ressource, int> inventory, int level)
    {
        UtilsAI utils;
        std::vector<std::pair<Commands, std::string>> commands;
        std::vector<Ressource> missingStones;
        int closestIndex = -1;
        Ressource closestStone;
        for (auto &stone : _neededStoneLevel[level - 1]) {
            if (inventory[stone.first] < stone.second)
                missingStones.push_back(stone.first);
        }
        std::reverse(missingStones.begin(), missingStones.end()); 
        for (auto &stone: missingStones) {
            for (size_t i = 0; i < look.size(); i++) {
                for (size_t j = 0; j < look[i].size(); j++) {
                    if (look[i][j] == stone) {
                        if (closestIndex == -1 || utils.goToCase(i).size() < utils.goToCase(closestIndex).size())
                            closestIndex = i;
                    }
                }
            }
            if (closestIndex != -1) {// si on a trouvé une ressource plus rare que la prochaine, on arrete
                closestStone = stone;
                break;
            }
        }
        if (closestIndex == -1) {
            commands = {{(Commands)(rand() % 2 + 1), ""}, {FORWARD, ""}, {LOOK, ""}};
            return commands;
        }
        commands = utils.goToCase(closestIndex);
        commands.push_back({TAKE, _stoneNames[closestStone]});
        commands.push_back({LOOK, ""});
        return commands;
    }
};
