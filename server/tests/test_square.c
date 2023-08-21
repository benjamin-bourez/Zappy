/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** test_square
*/

#include <criterion/criterion.h>
#include "server.h"
#include "square.h"

Test(square, creation)
{
    square_t *new_square = create_square();

    cr_assert_not_null(new_square);
    cr_assert_eq(new_square->x, 0);
    cr_assert_eq(new_square->y, 0);
    cr_assert_eq(new_square->food, 0);
    cr_assert_eq(new_square->linemate, 0);
    cr_assert_eq(new_square->deraumere, 0);
    cr_assert_eq(new_square->sibur, 0);
    cr_assert_eq(new_square->mendiane, 0);
    cr_assert_eq(new_square->phiras, 0);
    cr_assert_eq(new_square->thystame, 0);
    destroy_square(new_square);
}

Test(square, assign_position)
{
    square_t *new_square = create_square_pos(1, 2);

    cr_assert_not_null(new_square);
    cr_assert_eq(new_square->x, 1);
    cr_assert_eq(new_square->y, 2);
    cr_assert_eq(new_square->food, 0);
    cr_assert_eq(new_square->linemate, 0);
    cr_assert_eq(new_square->deraumere, 0);
    cr_assert_eq(new_square->sibur, 0);
    cr_assert_eq(new_square->mendiane, 0);
    cr_assert_eq(new_square->phiras, 0);
    cr_assert_eq(new_square->thystame, 0);
    destroy_square(new_square);
}

Test(square, add_resource)
{
    square_t *new_square = create_square_pos(1, 2);

    cr_assert_not_null(new_square);
    add_resources(new_square, FOOD);
    cr_assert_eq(new_square->food, 1);
    add_resources(new_square, LINEMATE);
    cr_assert_eq(new_square->linemate, 1);
    add_resources(new_square, DERAUMERE);
    cr_assert_eq(new_square->deraumere, 1);
    add_resources(new_square, SIBUR);
    cr_assert_eq(new_square->sibur, 1);
    add_resources(new_square, MENDIANE);
    cr_assert_eq(new_square->mendiane, 1);
    add_resources(new_square, PHIRAS);
    cr_assert_eq(new_square->phiras, 1);
    add_resources(new_square, THYSTAME);
    cr_assert_eq(new_square->thystame, 1);
    destroy_square(new_square);
}

Test(square, get_existing_ressources)
{
    square_t *new_square = create_square_pos(1, 2);

    cr_assert_not_null(new_square);
    new_square->food = 1;
    cr_assert_eq(get_ressources(new_square, FOOD), true);
    cr_assert_eq(new_square->food, 0);
    destroy_square(new_square);
}

Test(square, get_non_existing_ressources)
{
    square_t *new_square = create_square_pos(1, 2);

    cr_assert_not_null(new_square);
    cr_assert_eq(get_ressources(new_square, FOOD), false);
    destroy_square(new_square);
}

Test(square, destroy)
{
    square_t *new_square = create_square_pos(1, 2);

    cr_assert_not_null(new_square);
    cr_assert_eq(destroy_square(NULL), 84);
    cr_assert_eq(destroy_square(new_square), 0);
}
