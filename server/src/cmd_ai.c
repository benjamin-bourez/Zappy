/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_ai
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "server.h"
#include "commands_ai.h"

static void (*cmd[12])(server_t *, user_t *, [[maybe_unused]] char *) = {
    &ai_forward,
    &ai_right,
    &ai_left,
    &ai_look,
    &ai_inventory,
    &ai_broadcast,
    &ai_connect_nbr,
    &ai_fork,
    &ai_eject,
    &ai_take,
    &ai_set,
    &incantation_end
};

static const char *cmd_name[12] = {
    "Forward",
    "Right",
    "Left",
    "Look",
    "Inventory",
    "Broadcast",
    "Connect_nbr",
    "Fork",
    "Eject",
    "Take",
    "Set",
    "Incantation"
};

static const long int cmd_time[12] = {
    7000000,
    7000000,
    7000000,
    7000000,
    1000000,
    7000000,
    0,
    40000000,
    7000000,
    7000000,
    7000000,
    300000000
};

static int check_food(server_t *server, user_t *user)
{
    if (user->player->last_food_eaten <= 0) {
        user->player->inventory[0]--;
        user->player->last_food_eaten = 126.0 / server->map->freq * 1000000;
    }
    if (user->player->inventory[0] <= -1) {
        ai_death(server, user);
        return 1;
    }
    if (user->player->time > 0)
        return 1;
    return 0;
}

static int check_take_set(user_t *tmp, server_t *server, int i, int idx)
{
    char *arg = NULL;
    if (strncmp(tmp->buffer, cmd_name[i], strlen(cmd_name[i])) == 0
        && (i == 9 || i == 10)) {
        arg = strdup(tmp->buffer);
        idx = check_obj_name(arg);
        free(arg);
        if (idx != -1)
            tmp->player->time = cmd_time[i] / server->map->freq;
        return 0;
    }
    return 1;
}

static int check_command(user_t *tmp, server_t *server, int i)
{
    int idx = 0;

    if ((strncmp(tmp->buffer, cmd_name[i], strlen(cmd_name[i])) == 0
        && i == 11 && ai_incantation(server, tmp, tmp->buffer)) ||
        (strncmp(tmp->buffer, cmd_name[i], strlen(cmd_name[i])) == 0
        && i == 7 && ai_forking(tmp, tmp->buffer))) {
        tmp->player->time = cmd_time[i] / server->map->freq;
        return 0;
    }
    if (check_take_set(tmp, server, i, idx) == 0)
        return 0;
    if (strncmp(tmp->buffer, cmd_name[i], strlen(cmd_name[i])) == 0
        && i != 11) {
        tmp->player->time = cmd_time[i] / server->map->freq;
        return 0;
    }
    return 0;
}

static int get_command(user_t *tmp, server_t *server)
{
    if (tmp->buffer == NULL) {
        tmp->buffer = read_circular_buffer_string(tmp->cb);
        if (tmp->buffer == NULL)
            return 1;
        tmp->nb_cmd--;
    } else
        return 0;
    for (int i = 0; i < 12; i++)
        check_command(tmp, server, i);
    return 0;
}

int check_player(server_t *server, user_t *tmp)
{
    if (check_food(server, tmp))
        return 0;
    if (get_command(tmp, server))
        return 0;
    if (tmp->player->time > 0)
        return 0;
    for (int i = 0; i < 12; i++)
        if (strncmp(tmp->buffer, cmd_name[i], strlen(cmd_name[i])) == 0) {
            cmd[i](server, tmp, tmp->buffer);
            free(tmp->buffer);
            tmp->buffer = NULL;
            return 0;
        }
    free(tmp->buffer);
    tmp->buffer = NULL;
    dprintf(server->sd, "ko\n");
    tmp->nb_cmd++;
    return 0;
}
