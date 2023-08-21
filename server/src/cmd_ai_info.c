/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_ai_info
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "commands_ai.h"
#include "commands_gui.h"

void ai_look(server_t *server, user_t *user, [[maybe_unused]] char *arg)
{
    if (user->player->orientation == NORTH)
        ai_look_north(server, user);
    if (user->player->orientation == EAST)
        ai_look_east(server, user);
    if (user->player->orientation == SOUTH)
        ai_look_south(server, user);
    if (user->player->orientation == WEST)
        ai_look_west(server, user);
}

void ai_inventory(server_t *server, user_t *user, [[maybe_unused]] char *arg)
{
    dprintf(server->sd, "[ food %d, linemate %d, deraumere %d, sibur %d, \
mendiane %d, phiras %d, thystame %d ]\n",
        user->player->inventory[0],
        user->player->inventory[1],
        user->player->inventory[2],
        user->player->inventory[3],
        user->player->inventory[4],
        user->player->inventory[5],
        user->player->inventory[6]);
    send_player_inv(user);
}

void ai_broadcast(server_t *server, user_t *user, [[maybe_unused]] char *arg)
{
    user_t *tmp = user->first;
    char *str = strtok(arg, " ");

    str = strtok(NULL, "\n");
    while (tmp) {
        if (tmp->type == PLAYER && tmp != user)
            dprintf(tmp->socket, "message %d, %s\n",
                get_orientation(server, user, tmp), str);
        tmp = tmp->next;
    }
    send_broadcast_gui(user, str);
    dprintf(server->sd, "ok\n");
}
