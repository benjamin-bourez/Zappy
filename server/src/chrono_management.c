/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** chrono_management
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "server.h"

timeout_t *create_timeout(void)
{
    timeout_t *timeout = malloc(sizeof(timeout_t));

    if (timeout == NULL)
        return NULL;
    timeout->tv_sec = 0;
    timeout->tv_usec = 0;
    return timeout;
}

static long int update_users_select(user_t *users)
{
    long int time_max = __LONG_MAX__;

    while (users != NULL) {
        if (users->player && users->player->time < time_max &&
        users->player->time > 0) {
            time_max = users->player->time;
        }
        if (users->player && users->player->last_food_eaten < time_max &&
        users->player->last_food_eaten > 0) {
            time_max = users->player->last_food_eaten;
        }
        users = users->next;
    }
    return time_max;
}

int update_select(server_t *server, user_t *users, timeout_t *timeout)
{
    egg_t *egg = server->eggs;
    long int time_max = update_users_select(users);

    while (egg != NULL) {
        if (egg->time < time_max && egg->time > 0)
            time_max = egg->time;
        egg = egg->next;
    }
    if (server->last_update < time_max && server->last_update > 0)
        time_max = server->last_update;
    timeout->tv_sec = time_max / 1000000;
    timeout->tv_usec = time_max % 1000000;
    return timeout->tv_sec * 1000000 + timeout->tv_usec;
}

int update_time(server_t *server, user_t *user, timeout_t *timeout,
long int total_timeout)
{
    long int remaining_timeout = total_timeout -
    (timeout->tv_sec * 1000000 + timeout->tv_usec);
    user_t *first_user = user;

    if (server->last_update <= 0)
        update_total_object(server, server->map, user);
    while (user != NULL) {
        if (user->player->time > 0) {
            user->player->time -= remaining_timeout;
        }
        if (user->player->last_food_eaten > 0) {
            user->player->last_food_eaten -= remaining_timeout;
        }
        user = user->next;
    }
    update_eggs_life(server, server->eggs, remaining_timeout, first_user);
    if (server->last_update > 0)
        server->last_update -= remaining_timeout;
    return 0;
}
