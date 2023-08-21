/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** team_id
*/

#include <string.h>
#include "server.h"

int get_team_id(server_t *server, char *team_name)
{
    team_t *team = server->team;
    int id = 1;

    for (; team != NULL; team = team->next) {
        if (strcmp(team->name, team_name) == 0)
            return id;
        id++;
    }
    return -1;
}
