/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** world_creation
*/

#include <stdlib.h>

#include "server.h"
#include "square.h"
#include "commands_gui.h"

static float density[7] = {0.3, 0.15, 0.1, 0.1, 0.08, 0.05, 0.5};

int update_total_object(server_t *server, map_t *map, user_t *user)
{
    float nbr_object = 0;
    int *ressources[7] = {&(map->total_object->linemate),
    &(map->total_object->deraumere), &(map->total_object->sibur),
    &(map->total_object->mendiane), &(map->total_object->phiras),
    &(map->total_object->thystame), &(map->total_object->food)};

    if (!map || !map->total_object || !map->tilesmap)
        return 84;
    for (int i = 0; i < 7; i++) {
        nbr_object = (map->x * map->y * density[i]) - *ressources[i];
        for (int j = 0, y = rand() % map->y, x = rand() % map->x;
        j < nbr_object; j++, y = rand() % map->y, x = rand() % map->x) {
            add_resources(map->tilesmap[y][x], i);
            send_map_tile(server, user, x, y);
            (*ressources[i])++;
        }
    }
    server->last_update = 20 / map->freq * 1000000;
    return 0;
}

square_t **generate_line(square_t **line, int i, int width)
{
    int j = 0;
    for (; j < width; j++) {
        line[j] = create_square_pos(j, i);
        if (!line[j])
            return (NULL);
    }
    line[j] = NULL;
    return (line);
}

map_t *generate_tilesmap(map_t *map)
{
    int i = 0;

    if (!map || map->x <= 0 || map->y <= 0)
        return (NULL);
    map->tilesmap = malloc(sizeof(tilesmap_t) * (map->y + 1));
    if (!map->tilesmap)
        return (NULL);
    for (; i < map->y; i++) {
        map->tilesmap[i] = malloc(sizeof(square_t *) * (map->x + 1));
        if (!map->tilesmap[i])
            return (NULL);
        map->tilesmap[i] = generate_line(map->tilesmap[i], i, map->x);
        if (!map->tilesmap[i])
            return (NULL);
    }
    map->tilesmap[i] = NULL;
    return (map);
}

map_t *generate_objects(map_t *map)
{
    float nbr_objects = 0.0f;
    int *ressources[7] = {&(map->total_object->linemate),
    &(map->total_object->deraumere), &(map->total_object->sibur),
    &(map->total_object->mendiane), &(map->total_object->phiras),
    &(map->total_object->thystame), &(map->total_object->food)};

    if (!map || !map->tilesmap)
        return (NULL);
    for (int i = 0; i < 7; i++) {
        nbr_objects = (float) (map->x * map->y) * density[i];
        *ressources[i] = nbr_objects;
        for (int j = 0; j < nbr_objects; j++) {
            add_resources(map->tilesmap[rand() % map->y][rand() % map->x], i);
        }
    }
    return (map);
}

int destroy_tilesmap(tilesmap_t *tilesmap)
{
    if (!tilesmap)
        return 84;
    for (int i = 0; tilesmap[i]; i++) {
        for (int j = 0; tilesmap[i][j]; j++) {
            destroy_square(tilesmap[i][j]);
        }
        free(tilesmap[i]);
    }
    free(tilesmap);
    return 0;
}
