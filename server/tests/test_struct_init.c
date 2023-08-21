/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** tests_struct_init
*/

#include <criterion/criterion.h>

#include "server.h"

Test(server, creation)
{
    server_t *server = init_server();

    cr_assert_not_null(server);
    cr_assert_not_null(server->map);
    cr_assert_eq(server->map->x, 10);
    cr_assert_eq(server->map->y, 10);
    cr_assert_eq(server->map->freq, 100);
    cr_assert_eq(server->map->nb_p_player, 10);
    cr_assert_null(server->map->tilesmap);
    destroy_server(server);
}

Test(user, creation)
{
    user_t *user = init_user(NULL);

    cr_assert_not_null(user);
    cr_assert_eq(user->socket, 0);
    cr_assert_eq(user->type, NONE);
    cr_assert_null(user->team_name);
    cr_assert_not_null(user->cb);
    cr_assert_eq(user->nb_cmd, 0);
    cr_assert_null(user->first);
    cr_assert_null(user->next);
    destroy_user(user);
}

Test(team, creation)
{
    team_t *team = init_team("test", 10, NULL);

    cr_assert_not_null(team);
    cr_assert_str_eq(team->name, "test");
    cr_assert_eq(team->nb_player, 10);
    cr_assert_null(team->next);
    destroy_team(team);
}

Test(destroy, bad_destruction)
{
    destroy_server(NULL);
    destroy_user(NULL);
    destroy_team(NULL);
}
