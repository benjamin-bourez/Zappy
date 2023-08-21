/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** wait_list_creation
*/

#include <stdlib.h>
#include <stdbool.h>

#include "server.h"

wait_node_t *create_node(user_t *user)
{
    wait_node_t *new = malloc(sizeof(wait_node_t));

    if (new == NULL)
        return NULL;
    new->user = user;
    new->next = NULL;
    return new;
}

int add_to_list(wait_list_t *list, user_t *user)
{
    wait_node_t *new = NULL;
    wait_node_t *temp = NULL;

    if (list == NULL)
        return 84;
    new = create_node(user);
    if (new == NULL)
        return 84;
    if (list->first == NULL) {
        list->first = new;
    } else {
        for (temp = list->first; temp->next; temp = temp->next);
        temp->next = new;
    }
    list->size += 1;
    return 0;
}

bool is_in_list(wait_list_t *list, user_t *user)
{
    wait_node_t *temp = NULL;

    if (list == NULL)
        return false;
    for (temp = list->first; temp; temp = temp->next) {
        if (temp->user == user)
            return true;
    }
    return false;
}

wait_list_t *create_list(void)
{
    wait_list_t *new = malloc(sizeof(wait_list_t));

    if (new == NULL)
        return NULL;
    new->first = NULL;
    new->size = 0;
    return new;
}
