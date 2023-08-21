/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** send_information_gui
*/

#include <stdio.h>
#include <string.h>

#include "commands_gui.h"
#include "server.h"

void send_time_unit(server_t *server, user_t *user)
{
    char str[128] = {0};

    sprintf(str, "sgt %d\n", server->map->freq);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_time_modif(server_t *server, user_t *user)
{
    char str[128] = {0};

    sprintf(str, "sst %d\n", server->map->freq);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_end_game(user_t *user, char *team_name)
{
    char str[128] = {0};

    if (team_name == NULL)
        return;
    sprintf(str, "seg %s\n", team_name);
    if (user && user->first)
        send_to_gui(user->first, str);
}

void send_message(user_t *user, char *msg)
{
    char str[2048] = {0};

    if (msg == NULL)
        return;
    sprintf(str, "smg ");
    strcat(str, msg);
    strcat(str, "\n");
    if (user && user->first)
        send_to_gui(user->first, str);
}

void print_first_info(server_t *server)
{
    dprintf(server->sd, "msz %d %d\n", server->map->x, server->map->y);
    dprintf(server->sd, "sgt %d\n", server->map->freq);
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
    for (team_t *team = server->team; team != NULL; team = team->next)
        dprintf(server->sd, "tna %s\n", team->name);
}
