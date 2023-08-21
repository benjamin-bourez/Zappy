/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** *
*/

#include <stdlib.h>

#include "server.h"
#include "commands_gui.h"

static int remove_one_team(server_t *server, char *team_name)
{
    team_t *temp = server->team;

    while (temp) {
        if (temp->name == team_name)
            temp->nb_player--;
        temp = temp->next;
    }
    return 0;
}

static int kill_eggs(server_t *server, egg_t *egg, user_t *user)
{
    egg_t *tmp = egg;

    while (tmp != NULL) {
        if (tmp->food <= -1) {
            send_egg_dead(user, tmp->id);
            remove_one_team(server, tmp->team_name);
            tmp = remove_egg(tmp, tmp->id);
            server->eggs = tmp;
            continue;
        }
        tmp = tmp->next;
    }
    return 0;
}

int update_eggs_life(server_t *server, egg_t *egg, long int remaining_timeout,
user_t *user)
{
    egg_t *tmp = egg;

    while (tmp != NULL) {
        if (tmp->time > 0)
            tmp->time -= remaining_timeout;
        tmp = tmp->next;
    }
    tmp = egg;
    while (tmp != NULL) {
        if (tmp->time <= 0) {
            tmp->food--;
            tmp->time = 126.0 / server->map->freq * 1000000;
        }
        tmp = tmp->next;
    }
    return kill_eggs(server, egg, user);
}
