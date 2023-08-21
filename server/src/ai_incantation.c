/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_incantation
*/

#include <stdio.h>

#include "server.h"
#include "commands_ai.h"
#include "commands_gui.h"

static const int incantation_needs[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

static int check_incantation(user_t *tmp, user_t *user, user_t *player_list[],
int *nb_player)
{
    for (; tmp != NULL; tmp = tmp->next)
        if (tmp->type == PLAYER && tmp->player->x == user->player->x &&
            tmp->player->y == user->player->y &&
            tmp->player->level == user->player->level) {
                player_list[*nb_player] = tmp;
                (*nb_player)++;
        }
    if (*nb_player != incantation_needs[user->player->level - 1][0])
        return 1;
    return 0;
}

static void apply_incantation(user_t *player, user_t *user, int error)
{
    static int win = 0;

    if (player->player->is_incanting == false)
        return;
    if (error)
        dprintf(player->socket, "ko\n");
    else
        success_incantation(player, win);
    player->player->is_incanting = false;
    if (player->player->id != user->player->id) {
        player->player->time = player->player->save_time;
        player->player->save_time = 0;
    }
}

static void supress_stones_incantation
(server_t *server, int *server_obj[7], user_t *user)
{
    int *max_obj[7] = {&server->map->total_object->food,
        &server->map->total_object->linemate,
        &server->map->total_object->deraumere,
        &server->map->total_object->sibur,
        &server->map->total_object->mendiane,
        &server->map->total_object->phiras,
        &server->map->total_object->thystame};

    for (int idx = 1; idx < 7; idx++) {
        *server_obj[idx] -= incantation_needs[user->player->level - 1][idx];
        max_obj[idx] -= incantation_needs[user->player->level - 1][idx];
    }
    send_map_tile(server, user, user->player->x, user->player->y);
}

void incantation_end(server_t *server, user_t *user, [[maybe_unused]] char *)
{
    user_t *tmp = user->first;
    user_t *player_list[6];
    int nb_player = 0;
    square_t *tile =
        server->map->tilesmap[user->player->y][user->player->x];
    int *server_obj[7] = {&tile->food, &tile->linemate, &tile->deraumere,
    &tile->sibur, &tile->mendiane, &tile->phiras, &tile->thystame};
    int error = check_incantation(tmp, user, player_list, &nb_player);

    if (check_incantation_fail(1, 1, 0) == 1) {
        check_incantation_fail(0, 0, 0);
        return;
    }
    for (int idx = 1; idx < 7; idx++)
        if (*server_obj[idx] < incantation_needs[user->player->level - 1][idx])
            error = 1;
    if (error == 0)
        supress_stones_incantation(server, server_obj, user);
    for (int idx = 0; idx < nb_player; idx++)
        apply_incantation(player_list[idx], user, error);
}

bool ai_incantation(server_t *server, user_t *user, [[maybe_unused]] char *)
{
    user_t *tmp = user->first;
    user_t *player_list[6];
    int nb_player = 0;
    const square_t *tile =
        server->map->tilesmap[user->player->y][user->player->x];
    const int server_obj[7] = {tile->food, tile->linemate, tile->deraumere,
        tile->sibur, tile->mendiane, tile->phiras, tile->thystame};
    int error = check_incantation(tmp, user, player_list, &nb_player);

    for (int idx = 1; idx < 7; idx++)
        if (server_obj[idx] < incantation_needs[user->player->level - 1][idx])
            error = 1;
    if (error) {
        check_incantation_fail(0, 1, server->sd);
        return false;
    } else
        add_time(server, user, nb_player, player_list);
    send_incantation_start(user);
    return true;
}
