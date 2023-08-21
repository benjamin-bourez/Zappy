/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_ai_action
*/

#include <stdio.h>
#include <string.h>

#include "server.h"
#include "commands_ai.h"
#include "commands_gui.h"

static const char *obj_name[7] = { "food", "linemate", "deraumere", "sibur",
"mendiane", "phiras", "thystame"};

static void update_take_ai(server_t *server, user_t *user, int idx,
int *server_obj[7])
{
    int *max_obj[7] = {&server->map->total_object->food,
        &server->map->total_object->linemate,
        &server->map->total_object->deraumere,
        &server->map->total_object->sibur,
        &server->map->total_object->mendiane,
        &server->map->total_object->phiras,
        &server->map->total_object->thystame};

    *server_obj[idx] -= 1;
    *max_obj[idx] -= 1;
    user->player->inventory[idx] += 1;
    dprintf(server->sd, "ok\n");
    send_map_tile(server, user, user->player->x, user->player->y);
    send_collect(user, idx);
}

int check_obj_name(char *arg)
{
    char *object = strtok(arg, " ");
    int idx = -1;

    object = strtok(NULL, " ");
    for (int i = 0; i < 7; i++)
        if (object && strcmp(obj_name[i], object) == 0)
            idx = i;
    return idx;
}

void ai_take(server_t *server, user_t *user, char *arg)
{
    square_t *tilemap =
        server->map->tilesmap[user->player->y][user->player->x];
    int *server_obj[7] = {&tilemap->food, &tilemap->linemate,
        &tilemap->deraumere, &tilemap->sibur, &tilemap->mendiane,
        &tilemap->phiras, &tilemap->thystame};
    int idx = check_obj_name(arg);

    if (idx != -1 && *server_obj[idx] > 0)
        update_take_ai(server, user, idx, server_obj);
    else
        dprintf(server->sd, "ko\n");
}

void ai_set(server_t *server, user_t *user, char *arg)
{
    square_t *tilemap =
        server->map->tilesmap[user->player->y][user->player->x];
    int *server_obj[7] = {&tilemap->food, &tilemap->linemate,
        &tilemap->deraumere, &tilemap->sibur, &tilemap->mendiane,
        &tilemap->phiras, &tilemap->thystame};
    int idx = check_obj_name(arg);

    if (idx != -1) {
        *server_obj[idx] += 1;
        user->player->inventory[idx] -= 1;
        dprintf(server->sd, "ok\n");
        send_map_tile(server, user, user->player->x, user->player->y);
        send_drop(user, idx);
    } else
        dprintf(server->sd, "ko\n");
}
