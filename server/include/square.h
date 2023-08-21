/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** square
*/

#pragma once

#include <stdbool.h>
#include "server.h"

typedef struct square_s square_t;
typedef struct map_s map_t;
typedef square_t **tilesmap_t;
typedef enum resource resource_t;

struct square_s {
    int x;
    int y;
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
};

typedef struct total_object_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} total_object_t;

square_t *create_square(void);
square_t *create_square_pos(int x, int y);
map_t *generate_tilesmap(map_t *map);
map_t *generate_objects(map_t *map);
bool get_ressources(square_t *square, resource_t ressource);
void add_resources(square_t *square, resource_t resource);
int destroy_square(square_t *square);
int destroy_tilesmap(tilesmap_t *tilesmap);
