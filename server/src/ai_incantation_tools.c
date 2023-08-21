/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_incantation_tools
*/

#include <stdio.h>
#include "server.h"
#include "commands_gui.h"

int check_incantation_fail(int flag, int value, int sd)
{
    static int fail = 0;

    if (flag == 0 && value == 1)
        dprintf(sd, "ko\n");
    if (flag == 0)
        fail = value;
    return fail;
}

void add_time(server_t *server, user_t *user, int nb_player,
user_t *p_list[])
{
    for (int idx = 0; idx < nb_player; idx++) {
        dprintf(p_list[idx]->socket, "Elevation underway\n");
        p_list[idx]->player->is_incanting = true;
        if (p_list[idx]->player->id != user->player->id) {
            p_list[idx]->player->save_time = p_list[idx]->player->time;
            p_list[idx]->player->time += 300000000 / server->map->freq + 1;
        }
    }
}

int success_incantation(user_t *player, int win)
{
    player->player->level++;
    dprintf(player->socket, "Current level: %d\n",
        player->player->level);
    send_incantation_end(player, 1);
    send_player_level(player);
    if (player->player->level == 8 && win == 0) {
        send_end_game(player, player->team_name);
        win = 1;
    }
    return win;
}
