/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** manage_args
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "server.h"

int help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height \
-n name1 name2 ... -c clientsNb -f freq\n");
    printf("\tport\t\tis the port number\n");
    printf("\twidth\t\tis the width of the world\n");
    printf("\theight\t\tis the height of the world\n");
    printf("\tnameX\t\tis the name of the team X\n");
    printf("\tclientsNb\tis the number of authorized clients per team\n");
    printf("\tfreq\t\tis the reciprocal of time unit for execution of \
actions\n");
    return (0);
}

static void getargs_next(int opt, server_t *server)
{
    switch (opt) {
        case 'p':
            server->port = atoi(optarg);
            break;
        case 'x':
            server->map->x = atoi(optarg);
            break;
        case 'y':
            server->map->y = atoi(optarg);
            break;
        case 'c':
            server->map->nb_p_player = atoi(optarg);
            break;
        case '?':
            printf("Unknown option: %c\n", optopt);
            break;
        default:
            break;
    }
}

static void add_all_team(server_t *server, int ac, char **av)
{
    int i = 0;

    server->team = init_team(optarg, server->map->nb_p_player, NULL);
    server->team->first = server->team;
    while (optind + i < ac && av[optind + i][0] != '-')
        i++;
    for (int j = 0; j < i; j++) {
        server->team->next = init_team(av[optind + j],
            server->map->nb_p_player, server->team->first);
        server->team = server->team->next;
    }
    server->team = server->team->first;
}

void change_nb_p_player(server_t *server, int nb_p_player)
{
    team_t *tmp = server->team;

    server->map->nb_p_player = nb_p_player;
    while (tmp != NULL) {
        tmp->nb_player = server->map->nb_p_player;
        tmp = tmp->next;
    }
}

int getargs(int ac, char **av, server_t *server, int opt)
{
    while ((opt = getopt(ac, av, "hp:x:y:n:c:f:")) != -1) {
        switch (opt) {
            case 'n':
                add_all_team(server, ac, av);
                break;
            case 'c':
                change_nb_p_player(server, atoi(optarg));
                break;
            case 'f':
                server->map->freq = atoi(optarg);
                break;
            case 'h':
                help();
                return (1);
            default:
                getargs_next(opt, server);
                break;
        }
    }
    return (0);
}
