/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** init_struct
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "server.h"

static server_t *create_map(server_t *server)
{
    map_t *map = NULL;

    if (server == NULL)
        return NULL;
    server->wait_list = create_list();
    map = malloc(sizeof(map_t));
    if (map == NULL)
        return NULL;
    map->total_object = malloc(sizeof(total_object_t));
    if (map->total_object == NULL)
        return NULL;
    map->x = 10;
    map->y = 10;
    map->freq = 100;
    map->nb_p_player = 10;
    map->tilesmap = NULL;
    server->map = map;
    server->last_update = 0;
    server->eggs = NULL;
    return server;
}

data_ai_t *init_players(void)
{
    data_ai_t *players = malloc(sizeof(data_ai_t));

    if (players == NULL)
        return NULL;
    players->id = 0;
    players->x = 0;
    players->y = 0;
    players->level = 1;
    players->time = 0;
    players->last_food_eaten = 0;
    players->orientation = NORTH + (rand() % 4 * 2);
    players->is_incanting = false;
    players->save_time = 0;
    for (int i = 0; i < 7; i++)
        players->inventory[i] = 0;
    return players;
}

user_t *init_user(user_t *first)
{
    user_t *user = malloc(sizeof(user_t));

    if (user == NULL)
        return NULL;
    user->socket = 0;
    user->type = NONE;
    user->team_name = NULL;
    user->buffer = NULL;
    user->cb = malloc(sizeof(circular_buffer_t));
    user->player = init_players();
    cb_init(user->cb, 1024);
    user->nb_cmd = 0;
    user->first = first;
    user->next = NULL;
    if (user->cb == NULL || user->player == NULL) {
        destroy_user(user);
        return NULL;
    }
    return user;
}

team_t *init_team(char *name, int nb_p_player, team_t *first)
{
    team_t *team = malloc(sizeof(team_t));

    if (team == NULL)
        return NULL;
    team->name = name;
    team->nb_player = nb_p_player;
    team->next = NULL;
    team->first = first;
    return team;
}

server_t *init_server(void)
{
    server_t *server = malloc(sizeof(server_t));

    if (server == NULL)
        return NULL;
    server->port = 4242;
    server->master_socket = 0;
    server->new_socket = 0;
    server->activity = 0;
    server->sd = 0;
    server->max_sd = 0;
    server->opt = true;
    server->nb_client = 0;
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    server->addrlen = sizeof(server->address);
    fcntl(server->master_socket, F_SETFL,
    fcntl(server->master_socket, F_GETFL, 0) | O_NONBLOCK);
    server->team = NULL;
    return create_map(server);
}
