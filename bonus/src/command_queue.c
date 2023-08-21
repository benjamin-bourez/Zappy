/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** command_queue
*/

#include <stdlib.h>
#include <string.h>

#include "controller.h"

int add_command(command_queue_t *queue, char *command)
{
    command_node_t *node = NULL;

    if (queue == NULL)
        return (84);
    node = create_command_node(command);
    if (node == NULL)
        return (84);
    if (queue->first == NULL)
        queue->first = node;
    else {
        node->next = queue->first;
        queue->first = node;
    }
    queue->size++;
    return (0);
}

command_node_t *create_command_node(char *command)
{
    command_node_t *node = malloc(sizeof(command_node_t));

    if (node == NULL)
        return (NULL);
    node->command = strdup(command);
    if (node->command == NULL) {
        free(node);
        return (NULL);
    }
    node->next = NULL;
    return (node);
}

command_queue_t *create_command_queue(void)
{
    command_queue_t *queue = malloc(sizeof(command_queue_t));

    if (queue == NULL)
        return (NULL);
    queue->first = NULL;
    queue->size = 0;
    return (queue);
}

char *get_command(command_queue_t *queue)
{
    command_node_t *tmp = NULL;
    char *command = NULL;

    if (queue == NULL || queue->first == NULL)
        return NULL;
    tmp = queue->first;
    queue->first = queue->first->next;
    command = tmp->command;
    free(tmp);
    queue->size--;
    return (command);
}

int delete_command_queue(command_queue_t *queue)
{
    command_node_t *tmp = NULL;

    if (queue == NULL)
        return (84);
    while (queue->first != NULL) {
        tmp = queue->first;
        queue->first = queue->first->next;
        free(tmp->command);
        free(tmp);
    }
    free(queue);
    return (0);
}
