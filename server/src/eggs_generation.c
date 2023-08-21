/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** eggs_generation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

static egg_t *set_egg_value(int x, int y, char *team_name)
{
    static int id = 0;
    egg_t *new = malloc(sizeof(egg_t));

    if (new == NULL)
        return NULL;
    new->id = id++;
    new->x = x;
    new->y = y;
    new->orientation = (rand() % 4) * 2 + 1;
    new->team_name = team_name;
    new->food = 10;
    new->next = NULL;
    return new;
}

egg_t *create_egg(egg_t *egg, int pos[2], char *team_name, int frequence)
{
    egg_t *tmp = egg;
    egg_t *new = set_egg_value(pos[0], pos[1], team_name);

    if (new == NULL)
        return NULL;
    new->time = 126.0 / frequence * 1000000;
    if (egg)
        new->first = egg->first;
    else {
        new->first = new;
        return new;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return tmp->first;
}

team_t *check_team_exist(server_t *server, egg_t *egg, team_t *team)
{
    if (server->team && server->team->first) {
        team = server->team->first;
        return team;
    } else {
        free(egg);
        printf("No team exist\n");
        return NULL;
    }
}

egg_t *create_egg_team(int *map, server_t *server, team_t *team)
{
    for (int j = 0; j < team->nb_player; j++) {
        server->eggs = create_egg(server->eggs, (int [2]){rand() % map[0],
        rand() % map[1]}, team->name, server->map->freq);
        if (server->eggs == NULL)
            return NULL;
    }
    return server->eggs;
}

egg_t *generate_eggs(server_t *server)
{
    team_t *tmp = NULL;
    int map[2] = {server->map->x, server->map->y};

    server->eggs = NULL;
    if ((tmp = check_team_exist(server, server->eggs, tmp)) == NULL)
        return NULL;
    for (int i = 0; tmp != NULL; tmp = tmp->next, i++) {
        server->eggs = create_egg_team(map, server, tmp);
        if (server->eggs == NULL)
            return NULL;
    }
    return server->eggs;
}
