/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** test_word
*/

#include <stdio.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "server.h"
#include "square.h"

Test(tilesmap, generation)
{
    server_t *server = init_server();
    map_t *map;

    cr_assert_not_null(server);
    cr_assert_not_null(server->map);
    map = generate_tilesmap(server->map);
    cr_assert_not_null(map);
    cr_assert_not_null(map->tilesmap);
    cr_assert_eq(map->tilesmap[0][0]->x, 0);
    cr_assert_eq(map->tilesmap[0][0]->y, 0);
    destroy_server(server);
}

Test(tilesmap, generation_error)
{
    server_t *server = init_server();
    map_t *map;

    cr_assert_not_null(server);
    cr_assert_not_null(server->map);
    server->map->x = -1;
    map = generate_tilesmap(server->map);
    cr_assert_null(map);
    destroy_server(server);
}

Test(tilesmap, generation_map_null)
{
    map_t *map;

    map = generate_tilesmap(NULL);
    cr_assert_null(map);
}

Test(tilesmap, object_generation)
{
    server_t *server = init_server();
    map_t *map;

    cr_assert_not_null(server);
    cr_assert_not_null(server->map);
    map = generate_tilesmap(server->map);
    cr_assert_not_null(map);
    cr_assert_not_null(map->tilesmap);
    map = generate_objects(map);
}

Test(tilesmap, object_generation_map_null)
{
    map_t *map;

    map = generate_objects(NULL);
    cr_assert_null(map);
}
