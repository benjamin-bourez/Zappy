/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** test_circular_buffer
*/

#include <criterion/criterion.h>

#include "circular_buffer.h"

Test(circular_buffer, init)
{
    circular_buffer_t *cb = malloc(sizeof(circular_buffer_t));

    cb_init(cb, 1024);
    cr_assert(cb->buffer != NULL);
    cr_assert(cb->size == 1024);
    cr_assert(cb->head_buffer == cb->buffer);
    cr_assert(cb->queue_buffer == cb->buffer);
    cb_destroy(cb);
}

Test(circular_buffer, destroy_null)
{
    cb_destroy(NULL);
}

Test(circular_buffer, add)
{
    circular_buffer_t *cb = malloc(sizeof(circular_buffer_t));

    cb_init(cb, 2);
    add_to_buffer('a', cb);
    cr_assert(cb->queue_buffer == cb->buffer);
    cr_assert(cb->head_buffer == cb->buffer + 1);
    add_to_buffer('b', cb);
    cr_assert(cb->queue_buffer == cb->buffer + 1);
    cr_assert(cb->head_buffer == cb->buffer);
    cb_destroy(cb);
}

Test(circular_buffer, read)
{
    circular_buffer_t *cb = malloc(sizeof(circular_buffer_t));
    char *str;

    cb_init(cb, 4);
    add_to_buffer('a', cb);
    add_to_buffer('b', cb);
    add_to_buffer('\n', cb);
    str = read_circular_buffer_string(cb);
    cr_assert_str_eq(str, "ab");
    free(str);
    cb_destroy(cb);
}

Test(circular_buffer, read_empty)
{
    circular_buffer_t *cb = malloc(sizeof(circular_buffer_t));
    char *str;

    cb_init(cb, 4);
    str = read_circular_buffer_string(cb);
    cr_assert_null(str);
    cb_destroy(cb);
}

Test(circular_buffer, is_empty)
{
    circular_buffer_t *cb = malloc(sizeof(circular_buffer_t));

    cb_init(cb, 4);
    cr_assert(is_buffer_empty(cb));
    add_to_buffer('a', cb);
    cr_assert(!is_buffer_empty(cb));
    cb_destroy(cb);
}

Test(circular_buffer, bad_init)
{
    cb_init(NULL, 0);
}
