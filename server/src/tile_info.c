/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** tile_info
*/

#include <stdio.h>
#include "server.h"

void print_ressources(square_t *square, server_t *server)
{
    for (int i = square->food; i > 0; i--)
        dprintf(server->sd, " food");
    for (int i = square->linemate; i > 0; i--)
        dprintf(server->sd, " linemate");
    for (int i = square->deraumere; i > 0; i--)
        dprintf(server->sd, " deraumere");
    for (int i = square->sibur; i > 0; i--)
        dprintf(server->sd, " sibur");
    for (int i = square->mendiane; i > 0; i--)
        dprintf(server->sd, " mendiane");
    for (int i = square->phiras; i > 0; i--)
        dprintf(server->sd, " phiras");
    for (int i = square->thystame; i > 0; i--)
        dprintf(server->sd, " thystame");
}

void get_players_at_pos(server_t *server, int x, int y, user_t *user)
{
    user_t *tmp = user;

    while (tmp) {
        if (tmp->type == PLAYER && tmp->player->x == x
        && tmp->player->y == y)
            dprintf(server->sd, " player");
        tmp = tmp->next;
    }
}
