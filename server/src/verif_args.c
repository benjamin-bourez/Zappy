/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** verif_arg
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static int add_default_team(server_t *server)
{
    char *team_name[3] = {"Team2", "Team3", "Team4"};

    server->team = init_team("Team1", server->map->nb_p_player, NULL);
    if (server->team == NULL)
        return (84);
    server->team->first = server->team;
    for (int i = 0; i < 3; i++) {
        server->team->next = init_team(team_name[i], server->map->nb_p_player,
            server->team->first);
        if (server->team->next == NULL)
            return (84);
        server->team = server->team->next;
    }
    return (0);
}

static int verif_map(server_t *server)
{
    if (server->map->x < 10 || server->map->x > 30) {
        printf("-x option only accepts integer values between 10 and 30\n");
        help();
        return (84);
    }
    if (server->map->y < 10 || server->map->y > 30) {
        printf("-y option only accepts integer values between 10 and 30\n");
        help();
        return (84);
    }
    if (server->map->freq < 1 || server->map->freq > 1000) {
        printf("-f option only accepts integer values between 1 and 1000\n");
        help();
        return (84);
    }
    return (0);
}

static int check_unique_team(server_t *server)
{
    team_t *tmp = server->team;
    team_t *first = tmp->next;

    while (tmp != NULL) {
        first = tmp->next;
        while (first != NULL && strcmp(first->name, tmp->name) != 0)
            first = first->next;
        if (first != NULL) {
            printf("Team name must be unique\n");
            help();
            return (84);
        }
        tmp = tmp->next;
    }
    return (0);
}

int verif_args(server_t *server)
{
    if (verif_map(server) == 84)
        return (84);
    if (server->map->nb_p_player < 1) {
        printf("-c option only accepts integer values \
greater or equal to 1\n");
        help();
        return (84);
    }
    if (server->port < 1024 || server->port > 65535) {
        printf("-p option only accepts int values between 1024 and 65535\n");
        help();
        return (84);
    }
    if (server->team == NULL)
        if (add_default_team(server) == 84) {
            server->team = server->team->first;
            return (84);
        }
    server->team = server->team->first;
    return (check_unique_team(server));
}
