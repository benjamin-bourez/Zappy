/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_broadcast_tools
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static const int nb_tiles[4][9] = {
    { NORTH, 2, 4, 3, 8, 6, 7, 1, 5 },
    { EAST, 4, 6, 5, 2, 8, 1, 3, 7 },
    { SOUTH, 6, 8, 7, 4, 2, 3, 5, 1 },
    { WEST, 8, 2, 1, 6, 4, 5, 7, 3 },
};

static int *get_tiles_xy(server_t *server, user_t *from, user_t *to)
{
    int x1 = to->player->x - from->player->x;
    int y1 = to->player->y - from->player->y;
    int x2 = server->map->x - abs(x1);
    int y2 = server->map->y - abs(y1);
    int *xy = malloc(sizeof(int) * 2);

    memset(xy, 0, sizeof(int) * 2);
    if (from->player->x < to->player->x)
        xy[0] = 1;
    if (from->player->y < to->player->y)
        xy[1] = 1;
    if (from->player->x > to->player->x)
        xy[0] = -1;
    if (from->player->y > to->player->y)
        xy[1] = -1;
    if (abs(x2) < abs(x1))
        xy[0] *= (-1);
    if (abs(y2) < abs(y1))
        xy[1] *= (-1);
    return (xy);
}

static int get_nb_tile(int orientation, int i)
{
    switch (orientation) {
        case (11):
            return (nb_tiles[i][1]);
        case (21):
            return (nb_tiles[i][2]);
        case (31):
            return (nb_tiles[i][3]);
        case (12):
            return (nb_tiles[i][4]);
        case (22):
            return (nb_tiles[i][5]);
        case (32):
            return (nb_tiles[i][6]);
        case (13):
            return (nb_tiles[i][7]);
        case (23):
            return (nb_tiles[i][8]);
        default:
            return (0);
    }
}

int get_orientation(server_t *server, user_t *from, user_t *to)
{
    int *xy = get_tiles_xy(server, from, to);
    int orientation = 0;
    int i = -1;

    if (to->player->x == from->player->x && to->player->y == from->player->y) {
        free(xy);
        return (0);
    }
    if (xy[0] == 1)
        orientation += 1;
    else
        orientation += xy[0] == -1 ? 2 : 3;
    if (xy[1] == 1)
        orientation += 10;
    else
        orientation += xy[1] == -1 ? 20 : 30;
    while (nb_tiles[++i][0] != to->player->orientation);
    if (xy)
        free(xy);
    return (get_nb_tile(orientation, i));
}
