/*
** EPITECH PROJECT, 2023
** B-NWP-400-TLS-4-1-myteams-benjamin.bourez
** File description:
** circular_buffer
*/

#include <stdlib.h>
#include "circular_buffer.h"

void cb_init(circular_buffer_t *cb, size_t size)
{
    if (cb == NULL)
        return;
    cb->buffer = malloc(sizeof(char) * size);
    cb->head_buffer = cb->buffer;
    cb->queue_buffer = cb->buffer;
    cb->size = size;
}

void cb_destroy(circular_buffer_t *cb)
{
    if (cb == NULL)
        return;
    if (cb->buffer != NULL)
        free(cb->buffer);
    free(cb);
}

void add_to_buffer(char str_to_and, circular_buffer_t *cb)
{
    *cb->head_buffer = str_to_and;
    cb->head_buffer = cb->buffer + (cb->head_buffer + 1 - cb->buffer) %
        cb->size;
    if (cb->head_buffer == cb->queue_buffer)
        cb->queue_buffer = cb->buffer + (cb->queue_buffer + 1
            - cb->buffer) % cb->size;
}

char *read_circular_buffer_string(circular_buffer_t *cb)
{
    char *str = malloc(cb->size);
    int i = 0;

    while (cb->queue_buffer != cb->head_buffer && i < cb->size) {
        str[i++] = *(cb->queue_buffer);
        cb->queue_buffer = (cb->queue_buffer == cb->buffer + cb->size - 1) ?
            cb->buffer : cb->queue_buffer + 1;
        if (i >= 1 && str[i - 1] == '\n') {
            str[i - 1] = '\0';
            return str;
        }
    }
    free(str);
    return NULL;
}

bool is_buffer_empty(circular_buffer_t *cb)
{
    return cb->queue_buffer == cb->head_buffer;
}
