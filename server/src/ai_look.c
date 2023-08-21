/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_look
*/

#include <stdio.h>
#include "server.h"
#include "commands_ai.h"

static void print_comma(int i, int j, server_t *server)
{
    if (i != j)
        dprintf(server->sd, ",");
}

void ai_look_north(server_t *server, user_t *user)
{
    int i = 0;
    int j = 0;
    int x_tmp = user->player->x;
    int y_tmp = user->player->y;

    dprintf(server->sd, "[");
    for (i = 0; i <= user->player->level; i++) {
        for (j = -i; j <= i; j++) {
            x_tmp = user->player->x + j;
            y_tmp = user->player->y - i;
            x_tmp = x_tmp < 0 ? server->map->x + x_tmp : x_tmp;
            x_tmp = x_tmp >= server->map->x ? x_tmp - server->map->x : x_tmp;
            y_tmp = y_tmp < 0 ? server->map->y + y_tmp : y_tmp;
            get_players_at_pos(server, x_tmp, y_tmp, user->first);
            print_ressources(server->map->tilesmap[y_tmp][x_tmp], server);
            print_comma(i, j, server);
        }
        print_comma(i, user->player->level, server);
    }
    dprintf(server->sd, "]\n");
}

void ai_look_east(server_t *server, user_t *user)
{
    int i = 0;
    int j = 0;
    int x_tmp = user->player->x;
    int y_tmp = user->player->y;

    dprintf(server->sd, "[");
    for (i = 0; i <= user->player->level; i++) {
        for (j = -i; j <= i; j++) {
            x_tmp = user->player->x + i;
            y_tmp = user->player->y + j;
            x_tmp = x_tmp >= server->map->x ? x_tmp - server->map->x : x_tmp;
            y_tmp = y_tmp >= server->map->y ? y_tmp - server->map->y : y_tmp;
            y_tmp = y_tmp < 0 ? server->map->y + y_tmp : y_tmp;
            get_players_at_pos(server, x_tmp, y_tmp, user->first);
            print_ressources(server->map->tilesmap[y_tmp][x_tmp], server);
            print_comma(i, j, server);
        }
        print_comma(i, user->player->level, server);
    }
    dprintf(server->sd, "]\n");
}

void ai_look_south(server_t *server, user_t *user)
{
    int i = 0;
    int j = 0;
    int x_tmp = user->player->x;
    int y_tmp = user->player->y;

    dprintf(server->sd, "[");
    for (i = 0; i <= user->player->level; i++) {
        for (j = i; j >= -i; j--) {
            x_tmp = user->player->x + j;
            y_tmp = user->player->y + i;
            x_tmp = x_tmp < 0 ? server->map->x + x_tmp : x_tmp;
            x_tmp = x_tmp >= server->map->x ? x_tmp - server->map->x : x_tmp;
            y_tmp = y_tmp >= server->map->y ? y_tmp - server->map->y : y_tmp;
            get_players_at_pos(server, x_tmp, y_tmp, user->first);
            print_ressources(server->map->tilesmap[y_tmp][x_tmp], server);
            print_comma(-i, j, server);
        }
        print_comma(i, user->player->level, server);
    }
    dprintf(server->sd, "]\n");
}

void ai_look_west(server_t *server, user_t *user)
{
    int i = 0;
    int j = 0;
    int x_tmp = user->player->x;
    int y_tmp = user->player->y;

    dprintf(server->sd, "[");
    for (i = 0; i <= user->player->level; i++) {
        for (j = i; j >= -i; j--) {
            x_tmp = user->player->x - i;
            y_tmp = user->player->y + j;
            x_tmp = x_tmp < 0 ? x_tmp + server->map->x : x_tmp;
            y_tmp = y_tmp >= server->map->y ? y_tmp - server->map->y : y_tmp;
            y_tmp = y_tmp < 0 ? server->map->y + y_tmp : y_tmp;
            get_players_at_pos(server, x_tmp, y_tmp, user->first);
            print_ressources(server->map->tilesmap[y_tmp][x_tmp], server);
            print_comma(-i, j, server);
        }
        print_comma(i, user->player->level, server);
    }
    dprintf(server->sd, "]\n");
}
