/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ManageFood
*/

#include "ManageFood.hpp"

namespace Zappy::AI
{
    std::vector<std::pair<Commands, std::string>> ManageFood::getCommand(std::vector<std::vector<Ressource>> look, std::pair<Commands, std::string> last_command)
    {
        (void)last_command;
        std::vector<std::pair<Commands, std::string>> commands;
        UtilsAI utils;
        int closestIndex = -1;

        for (size_t i = 0; i < look.size(); i++) {
            for (size_t j = 0; j < look[i].size(); j++) {
                if (look[i][j] == FOOD) {
                    if (closestIndex == -1 || utils.goToCase(i).size() < utils.goToCase(closestIndex).size())
                        closestIndex = i;
                }
            }
        }

        if (closestIndex == -1) {
            commands = {{(Commands)(rand() % 2 + 1), ""}, {FORWARD, ""}, {LOOK, ""}};
            return commands;
        }

        // if (utils.goToCase(closestIndex).size() >= 5) {
        //     commands = {{RIGHT, ""}, {FORWARD, ""}, {LOOK, ""}};
        //     return commands;
        // }

        commands = utils.goToCase(closestIndex);
        commands.push_back({TAKE, "food"});
        return commands;
    }
};
