/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** send_interaction_gui
*/

#include <stdio.h>
#include <string.h>

#include "commands_gui.h"
#include "server.h"

void send_expulse_gui(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "pex %d\n", user->player->id);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_broadcast_gui(user_t *user, char *msg)
{
    char str[2048] = {0};

    if (msg == NULL)
        return;
    sprintf(str, "pbc %d ", user->player->id);
    strcat(str, msg);
    strcat(str, "\n");
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_drop(user_t *user, int res)
{
    char str[128] = {0};

    if (str == NULL)
        return;
    sprintf(str, "pdr %d %d\n", user->player->id, res);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_collect(user_t *user, int res)
{
    char str[128] = {0};

    sprintf(str, "pgt %d %d\n", user->player->id, res);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_player_death(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "pdi %d\n", user->player->id);
    if (user && user->first)
        send_to_gui(user->first, str);
}
