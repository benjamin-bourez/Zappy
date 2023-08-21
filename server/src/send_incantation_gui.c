/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** send_incantation_gui
*/

#include <string.h>
#include <stdio.h>
#include "commands_gui.h"
#include "server.h"

void send_incantation_start(user_t *user)
{
    char str_tmp[256] = {0};
    char final_str[1024] = {0};

    sprintf(str_tmp, "pic %d %d %d %d", user->player->x, user->player->y,
    user->player->level, user->player->id);
    strcat(final_str, str_tmp);
    for (user_t *tmp = user->first; tmp != NULL; tmp = tmp->next) {
        if (tmp->player->x == user->player->x &&
        tmp->player->y == user->player->y &&
        tmp->player->id != user->player->id) {
            sprintf(str_tmp, " %d", tmp->player->id);
            strcat(final_str, str_tmp);
        }
    }
    strcat(final_str, "\n");
    if (user && user->first)
        send_to_gui(user->first, final_str);
}

void send_incantation_end(user_t *user, int result)
{
    char str[128] = {0};

    sprintf(str, "pie %d %d %d\n", user->player->x, user->player->y, result);
    if (user && user->first)
        send_to_gui(user->first, str);
}
