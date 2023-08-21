/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** wait_list_destroy
*/

#include <stdlib.h>

#include "server.h"

int destroy_node(wait_node_t *node)
{
    if (node == NULL)
        return 84;
    free(node);
    return 0;
}

int remove_first(wait_list_t *list)
{
    wait_node_t *temp = NULL;

    if (list == NULL)
        return 84;
    temp = list->first;
    if (temp == NULL)
        return 84;
    list->first = temp->next;
    destroy_node(temp);
    return 0;
}

int remove_user(wait_list_t *list, user_t *user)
{
    wait_node_t *before = NULL;
    wait_node_t *temp = NULL;

    if (list == NULL || list->first == NULL)
        return 84;
    if (user == list->first->user)
        return remove_first(list);
    before = list->first;
    temp = list->first->next;
    while (temp) {
        if (temp->user == user) {
            before->next = temp->next;
            destroy_node(temp);
            temp = before->next;
            list->size--;
        } else {
            before = temp;
            temp = temp->next;
        }
    }
    return 0;
}

int destroy_list(wait_list_t *list)
{
    wait_node_t *temp = NULL;
    wait_node_t *next = NULL;

    if (list == NULL)
        return 84;
    temp = list->first;
    while (temp) {
        next = temp->next;
        destroy_node(temp);
        temp = next;
    }
    free(list);
    return 0;
}
