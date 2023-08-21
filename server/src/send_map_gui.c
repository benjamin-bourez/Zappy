/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** send_map_gui
*/

#include <stdio.h>
#include "commands_gui.h"
#include "server.h"

void send_map_size(server_t *server, user_t *user)
{
    char str[128] = {0};

    sprintf(str, "msz %d %d\n", server->map->x, server->map->y);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_map_tile(server_t *server, user_t *user, int x, int y)
{
    char str[128] = {0};

    sprintf(str, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    server->map->tilesmap[y][x]->food,
    server->map->tilesmap[y][x]->linemate,
    server->map->tilesmap[y][x]->deraumere,
    server->map->tilesmap[y][x]->sibur,
    server->map->tilesmap[y][x]->mendiane,
    server->map->tilesmap[y][x]->phiras,
    server->map->tilesmap[y][x]->thystame);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_all_map(server_t *server, user_t *user)
{
    for (int y = 0; y < server->map->y; y++) {
        for (int x = 0; x < server->map->x; x++) {
            send_map_tile(server, user, x, y);
        }
    }
}
