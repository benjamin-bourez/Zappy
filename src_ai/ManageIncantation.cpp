/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageIncantation
*/

#include "ManageIncantation.hpp"

namespace Zappy::AI
{
    ManageIncantation::ManageIncantation()
    {
        _neededStoneLevel = UtilsAI().getNeededStoneLevel();
        _neededPlayerLevel = {1, 2, 2, 4, 4, 6, 6, 10000};
    }

    ManageIncantation::~ManageIncantation()
    {
    }

    Incantation ManageIncantation::canIncant(std::vector<std::vector<Ressource>> look, std::map<Ressource, int> inventory, int level, Commands lastCommand)
    {
        (void)lastCommand;
        if (inventory[FOOD] <= 5)
            return NOTENOUGHFOOD;
        if (lookEnoughStones(look, level) && gotEnoughPlayers(look, level) == 0)
            return SUCCESS;
        if (lookEnoughStones(look, level) == false) {
            if (gotEnoughStones(inventory, level) == false)
                return NOTENOUGHRESSOURCES;
            else
                return SETRESSOURCES;
        }
        if (gotEnoughPlayers(look, level) == -1)
            return NOTENOUGHPLAYER;
        if (gotEnoughPlayers(look, level) == 1)
            return TOOMANYPLAYER;
        return NOTENOUGHFOOD;
    }

    bool ManageIncantation::gotEnoughStones(std::map<Ressource, int> inventory, int level)
    {
        for (auto &stone : _neededStoneLevel[level - 1]) {
            if (inventory[stone.first] < stone.second)
                return false;
        }
        return true;
    }

    int ManageIncantation::gotEnoughPlayers(std::vector<std::vector<Ressource>> look, int level)
    {
        int nb_players = 0;

        for (auto &ressource : look[0]) {
            if (ressource == PLAYER)
                nb_players++;
        }
        if (nb_players == _neededPlayerLevel[level - 1])
            return 0;
        else if (nb_players < _neededPlayerLevel[level - 1])
            return -1;
        else
            return 1;
    }

    bool ManageIncantation::lookEnoughStones(std::vector<std::vector<Ressource>> look, int level)
    {
        int currentStoneCount = 0;

        for (auto &stone : _neededStoneLevel[level - 1]) {
            for (auto &ressource : look[0]) {
                currentStoneCount += (ressource == stone.first);
            }
            if (currentStoneCount < _neededStoneLevel[level - 1][stone.first]) {
                return false;
            }
            currentStoneCount = 0;
        }
        return true;
    }
}
