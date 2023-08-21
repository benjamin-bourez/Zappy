/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_eject_tools
*/

#include <stdio.h>
#include "server.h"
#include "commands_gui.h"

void ai_back(server_t *server, user_t *user)
{
    if (user->player->orientation == NORTH)
        user->player->y++;
    if (user->player->orientation == SOUTH)
        user->player->y--;
    if (user->player->orientation == EAST)
        user->player->x--;
    if (user->player->orientation == WEST)
        user->player->x++;
    if (user->player->x < 0)
        user->player->x = server->map->x - 1;
    if (user->player->y < 0)
        user->player->y = server->map->y - 1;
    if (user->player->x > server->map->x - 1)
        user->player->x = 0;
    if (user->player->y > server->map->y - 1)
        user->player->y = 0;
    dprintf(user->socket, "eject\n");
}

int ai_eject_eggs(server_t *server, user_t *user, egg_t *tmp_e)
{
    int nb_ejected = 0;

    while (tmp_e) {
        if (tmp_e->x == user->player->x && tmp_e->y == user->player->y) {
            send_egg_dead(user, tmp_e->id);
            server->eggs = remove_egg(server->eggs, tmp_e->id);
            nb_ejected++;
            tmp_e = server->eggs;
            continue;
        }
        tmp_e = tmp_e->next;
    }
    return (nb_ejected);
}
