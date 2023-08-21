/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** square_creation
*/

#include <stdlib.h>
#include <stdbool.h>
#include "square.h"
#include "server.h"

square_t *create_square(void)
{
    square_t *square = malloc(sizeof(square_t));

    if (!square)
        return (NULL);
    square->x = 0;
    square->y = 0;
    square->food = 0;
    square->linemate = 0;
    square->deraumere = 0;
    square->mendiane = 0;
    square->phiras = 0;
    square->sibur = 0;
    square->thystame = 0;
    return (square);
}

square_t *create_square_pos(int x, int y)
{
    square_t *square = create_square();

    if (!square)
        return (NULL);
    square->x = x;
    square->y = y;
    return (square);
}

void add_resources(square_t *square, resource_t resource)
{
    int *resources[7] = {&(square->linemate),
    &(square->deraumere), &(square->sibur), &(square->mendiane),
    &(square->phiras), &(square->thystame), &(square->food)};

    for (resource_t i = 0; i < 7; i++) {
        if (i == resource)
            *resources[i] += 1;
    }
}

bool get_ressources(square_t *square, resource_t ressource)
{
    int *resources[7] = {&(square->linemate),
    &(square->deraumere), &(square->sibur), &(square->mendiane),
    &(square->phiras), &(square->thystame), &(square->food)};

    for (resource_t i = 0; i < 7; i++) {
        if (i == ressource && *resources[i] > 0) {
            *resources[i] -= 1;
            return (true);
        }
    }
    return (false);
}

int destroy_square(square_t *square)
{
    if (!square)
        return 84;
    free(square);
    return 0;
}
