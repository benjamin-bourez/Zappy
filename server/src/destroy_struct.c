/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** destroy_struct
*/

#include <unistd.h>
#include <stdlib.h>
#include "server.h"

static void destroy_map(map_t *map)
{
    if (map == NULL)
        return;
    if (map->total_object)
        free(map->total_object);
    destroy_tilesmap(map->tilesmap);
    free(map);
}

void destroy_team(team_t *team)
{
    team_t *tmp = team;

    while (tmp != NULL) {
        team = team->next;
        free(tmp);
        tmp = team;
    }
}

void destroy_server(server_t *server)
{
    if (server == NULL)
        return;
    destroy_map(server->map);
    destroy_team(server->team);
    destroy_list(server->wait_list);
    destroy_eggs(server->eggs);
    free(server);
}

void destroy_user(user_t *user)
{
    if (user == NULL)
        return;
    if (user->socket != 0)
        close(user->socket);
    cb_destroy(user->cb);
    if (user->buffer)
        free(user->buffer);
    if (user->player)
        free(user->player);
    free(user);
}
