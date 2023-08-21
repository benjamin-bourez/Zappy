/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** send_egg_gui
*/

#include <stdio.h>
#include "commands_gui.h"
#include "server.h"

void send_egg_laying(user_t *user)
{
    char str[128] = {0};

    sprintf(str, "pfk %d\n", user->player->id);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_egg_laid(server_t *server, user_t *user)
{
    char str[128] = {0};
    egg_t *egg = server->eggs;

    if (egg == NULL)
        return;
    egg = egg->first;
    while (egg->next != NULL)
        egg = egg->next;
    sprintf(str, "enw %d %d %d %d\n",
    egg->id, user->player->id, egg->x, egg->y);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_egg_connection(user_t *user, int id)
{
    char str[128] = {0};

    sprintf(str, "ebo %d\n", id);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_egg_dead(user_t *user, int id)
{
    char str[128] = {0};

    sprintf(str, "edi %d\n", id);
    if (user && user->first)
        send_to_gui(user->first, str);
}
