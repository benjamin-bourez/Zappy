/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** eggs_destruction
*/

#include <stdlib.h>

#include "server.h"

void destroy_eggs(egg_t *egg)
{
    egg_t *tmp = egg;

    while (tmp != NULL) {
        egg = egg->next;
        free(tmp);
        tmp = egg;
    }
}

static egg_t *remove_first_egg(egg_t *egg)
{
    egg_t *tmp = egg->first;

    tmp = tmp->next;
    free(egg);
    if (tmp == NULL)
        return NULL;
    if (tmp->next == NULL)
        tmp->first = tmp;
    for (egg = tmp; egg->next != NULL; egg = egg->next)
        egg->first = tmp;
    egg->first = tmp;
    return tmp;
}

egg_t *remove_egg(egg_t *egg, int id)
{
    egg_t *tmp = egg->first;

    if (tmp->id == id)
        return remove_first_egg(egg);
    while (tmp->next != NULL) {
        if (tmp->next->id == id) {
            egg = tmp->next;
            tmp->next = egg->next;
            free(egg);
            return tmp->first;
        }
        tmp = tmp->next;
    }
    return tmp->first;
}
