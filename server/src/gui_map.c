/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** gui_map
*/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "str_to_word_array.h"

void map_size(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *)
{
    dprintf(server->sd, "msz %d %d\n", server->map->x, server->map->y);
}

void content_tile(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    char **tab = str_to_word_array(command, " ");
    char *endptrx = NULL;
    char *endptry = NULL;
    int x = 0;
    int y = 0;

    if (!tab || !tab[1] || !tab[2] || (x = strtol(tab[1], &endptrx, 10)) < 0
    || x >= server->map->x || (y = strtol(tab[2], &endptry, 10)) < 0
    || y >= server->map->y || endptrx == tab[1] || endptry == tab[2]) {
        dprintf(server->sd, "sbp\n");
        return free_word_array(tab);
    }
    free_word_array(tab);
    dprintf(server->sd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    server->map->tilesmap[y][x]->food, server->map->tilesmap[y][x]->linemate,
    server->map->tilesmap[y][x]->deraumere, server->map->tilesmap[y][x]->sibur,
    server->map->tilesmap[y][x]->mendiane, server->map->tilesmap[y][x]->phiras,
    server->map->tilesmap[y][x]->thystame);
}

void content_map(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    for (int y = 0; y < server->map->y; y++) {
        for (int x = 0; x < server->map->x; x++) {
            dprintf(server->sd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
            server->map->tilesmap[y][x]->food,
            server->map->tilesmap[y][x]->linemate,
            server->map->tilesmap[y][x]->deraumere,
            server->map->tilesmap[y][x]->sibur,
            server->map->tilesmap[y][x]->mendiane,
            server->map->tilesmap[y][x]->phiras,
            server->map->tilesmap[y][x]->thystame);
        }
    }
}
