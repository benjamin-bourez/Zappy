/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_ai_move
*/

#include <stdio.h>
#include "server.h"
#include "commands_ai.h"
#include "commands_gui.h"

void ai_forward(server_t *server, user_t *user, [[maybe_unused]] char *arg)
{
    if (user->player->orientation == NORTH)
        user->player->y--;
    if (user->player->orientation == SOUTH)
        user->player->y++;
    if (user->player->orientation == EAST)
        user->player->x++;
    if (user->player->orientation == WEST)
        user->player->x--;
    if (user->player->x < 0)
        user->player->x = server->map->x - 1;
    if (user->player->y < 0)
        user->player->y = server->map->y - 1;
    if (user->player->x > server->map->x - 1)
        user->player->x = 0;
    if (user->player->y > server->map->y - 1)
        user->player->y = 0;
    dprintf(server->sd, "ok\n");
    send_player_pos(user);
}

void ai_right(server_t *server, user_t *user, [[maybe_unused]] char *arg)
{
    user->player->orientation -= 2;
    user->player->orientation %= 8;
    if (user->player->orientation < 0)
        user->player->orientation += 8;
    dprintf(server->sd, "ok\n");
    send_player_pos(user);
}

void ai_left(server_t *server, user_t *user, [[maybe_unused]] char *arg)
{
    user->player->orientation += 2;
    if (user->player->orientation > 7)
        user->player->orientation = 1;
    dprintf(server->sd, "ok\n");
    send_player_pos(user);
}
