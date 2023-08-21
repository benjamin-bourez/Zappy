/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_ai_multi
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "commands_ai.h"
#include "commands_gui.h"

void ai_connect_nbr(server_t *server, user_t *user, char *)
{
    team_t *team = server->team;

    while (team) {
        if (team->name == user->team_name) {
            dprintf(server->sd, "%d\n", team->nb_player);
            return;
        }
        team = team->next;
    }
}

void ai_fork(server_t *server, user_t *user, char *)
{
    egg_t *tmp = create_egg(server->eggs, (int [2]){user->player->x,
    user->player->y}, user->team_name, server->map->freq);

    if (tmp == NULL)
        return ai_fork_return(server, user, -1);
    server->eggs = tmp;
    send_egg_laid(server, user);
    ai_fork_return(server, user, 1);
}

void check_eject_incantation(user_t *user)
{
    if (user->player->is_incanting == true
    && strncmp(user->buffer, "Incantation", 11) != 0) {
        dprintf(user->socket, "ko\n");
        user->player->is_incanting = false;
        user->player->time = user->player->save_time;
        user->player->save_time = 0;
    }
    if (user->player->is_incanting == true
    && strncmp(user->buffer, "Incantation", 11) == 0) {
        user->player->is_incanting = false;
        user->player->time = user->player->save_time;
        user->player->save_time = 0;
    }
}

void ai_eject(server_t *server, user_t *user, char *)
{
    int nb_ejected = 0;
    user_t *tmp_u = user->first;
    egg_t *tmp_e = server->eggs;

    while (tmp_u) {
        if (tmp_u->type == PLAYER && tmp_u != user &&
        tmp_u->player->x == user->player->x &&
        tmp_u->player->y == user->player->y) {
            ai_back(server, tmp_u);
            check_eject_incantation(tmp_u);
            nb_ejected++;
        }
        tmp_u = tmp_u->next;
    }
    nb_ejected += ai_eject_eggs(server, user, tmp_e);
    if (nb_ejected != 0) {
        dprintf(server->sd, "ok\n");
        send_expulse_gui(user);
    } else
        dprintf(server->sd, "ko\n");
}

void ai_death(server_t *server, user_t *user)
{
    dprintf(server->sd, "dead\n");
    server->nb_client--;
    reset_cb(user->cb);
    user->type = NONE;
    send_player_death(user);
    close(user->socket);
    user->socket = 0;
}
