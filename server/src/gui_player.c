/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** gui_player
*/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "str_to_word_array.h"

void name_teams(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    team_t *tmp = NULL;

    if (server->team == NULL)
        return;
    tmp = server->team->first;
    while (tmp != NULL) {
        dprintf(server->sd, "tna %s\n", tmp->name);
        tmp = tmp->next;
    }
}

int transform_orientation(int orientation)
{
    if (orientation == NORTH)
        return (1);
    if (orientation == EAST)
        return (2);
    if (orientation == SOUTH)
        return (3);
    if (orientation == WEST)
        return (4);
    return (0);
}

void player_pos(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    user_t *tmp = user->first;
    char **tab = str_to_word_array(command, " ");
    char *endptr = NULL;
    int id = 0;

    if (!tab || !tab[1] || (id = strtol(tab[1], &endptr, 10)) < 0
    || endptr == tab[1]) {
        dprintf(server->sd, "sbp\n");
        return free_word_array(tab);
    }
    free_word_array(tab);
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->type == PLAYER && tmp->player->id == id) {
            dprintf(server->sd, "ppo %d %d %d %d\n", tmp->player->id,
            tmp->player->x, tmp->player->y,
            transform_orientation(tmp->player->orientation));
            return;
        }
    }
    dprintf(server->sd, "sbp\n");
}

void player_level(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    user_t *tmp = user->first;
    char **tab = str_to_word_array(command, " ");
    char *endptr = NULL;
    int id = 0;

    if (!tab || !tab[1] || (id = strtol(tab[1], &endptr, 10)) < 0
    || endptr == tab[1]) {
        dprintf(server->sd, "sbp\n");
        return free_word_array(tab);
    }
    free_word_array(tab);
    for (; tmp != NULL; tmp = tmp->next) {
        if (tmp->type == PLAYER && tmp->player->id == id) {
            dprintf(server->sd, "plv %d %d\n", tmp->player->id,
            tmp->player->level);
            return;
        }
    }
    dprintf(server->sd, "sbp\n");
}

void player_inv(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    user_t *tmp = user->first;
    char **tb = str_to_word_array(command, " ");
    char *ptr = NULL;
    int id = 0;

    if (!tb || !tb[1] || (id = strtol(tb[1], &ptr, 10)) < 0 || ptr == tb[1]) {
        dprintf(server->sd, "sbp\n");
        return free_word_array(tb);
    }
    free_word_array(tb);
    for (; tmp != NULL; tmp = tmp->next)
        if (tmp->type == PLAYER && tmp->player->id == id) {
            dprintf(server->sd, "pin %d %d %d %d %d %d %d %d %d %d\n", tmp->
            player->id, tmp->player->x, tmp->player->y, tmp->player->inventory
            [0], tmp->player->inventory[1], tmp->player->inventory[2], tmp->
            player->inventory[3], tmp->player->inventory[4], tmp->player->
            inventory[5], tmp->player->inventory[6]);
            return;
        }
    dprintf(server->sd, "sbp\n");
}
