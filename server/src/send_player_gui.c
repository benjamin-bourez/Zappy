/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** send_player_gui
*/

#include <stdio.h>
#include <string.h>
#include "commands_gui.h"
#include "server.h"

void send_teams(server_t *server, user_t *user)
{
    team_t *tmp = server->team;
    char str[128] = {0};

    while (tmp != NULL) {
        memset(str, 0, 100);
        sprintf(str, "tna %s\n", tmp->name);
        if (user && user->first)
            send_to_gui(user->first, str);
        tmp = tmp->next;
    }
}

void send_new_player(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "pnw %d %d %d %d %d %s\n", user->player->id, user->player->x,
    user->player->y, transform_orientation(user->player->orientation),
    user->player->level, user->team_name);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_player_pos(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "ppo %d %d %d %d\n", user->player->id, user->player->x,
    user->player->y, transform_orientation(user->player->orientation));
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_player_level(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "plv %d %d\n", user->player->id, user->player->level);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_player_inv(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "pin %d %d %d %d %d %d %d %d %d %d\n", user->player->id,
    user->player->x, user->player->y, user->player->inventory[0],
    user->player->inventory[1], user->player->inventory[2],
    user->player->inventory[3], user->player->inventory[4],
    user->player->inventory[5], user->player->inventory[6]);
    if (user && user->first)
        send_to_gui(user->first, str);
}
