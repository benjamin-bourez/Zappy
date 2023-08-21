/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ai_fork
*/

#include <stdio.h>
#include <string.h>
#include "server.h"
#include "commands_ai.h"
#include "commands_gui.h"

static void add_slot_to_team(server_t *server, char *team_name, int nb)
{
    team_t *team = server->team;

    while (team) {
        if (strcmp(team->name, team_name) == 0) {
            team->nb_player += nb;
            return;
        }
        team = team->next;
    }
}

static int add_client(server_t *server, team_t *team)
{
    int nbr_to_destroy = 0;
    wait_node_t *temp = NULL;

    wait_node_t *lst_to_destroy[server->wait_list->size];
    temp = server->wait_list->first;
    while (temp) {
        if (strcmp(temp->user->team_name, team->name) == 0 &&
        player_connection(server, temp->user, team)) {
            lst_to_destroy[nbr_to_destroy] = temp;
            nbr_to_destroy++;
        }
        temp = temp->next;
    }
    for (int i = 0; i < nbr_to_destroy; i++)
        remove_user(server->wait_list, lst_to_destroy[i]->user);
    return 0;
}

static int add_waiting_client_to_egg(server_t *server)
{
    team_t *team = NULL;

    if (!server || !server->wait_list || !server->wait_list->first)
        return -1;
    for (team = server->team; team; team = team->next) {
        if (team->nb_player > 0) {
            add_client(server, team);
        }
    }
    return 0;
}

void ai_fork_return(server_t *server, user_t *user, int slot)
{
    if (slot == -1) {
        dprintf(server->sd, "ko\n");
        return;
    }
    add_slot_to_team(server, user->team_name, slot);
    add_waiting_client_to_egg(server);
    dprintf(server->sd, "ok\n");
    send_egg_laid(server, user);
}

bool ai_forking(user_t *user, char *)
{
    send_egg_laying(user);
    return true;
}
