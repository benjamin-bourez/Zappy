/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** connection
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "commands_gui.h"

static void set_user_value(user_t *user, egg_t *egg)
{
    user->player->id = egg->id;
    user->player->x = egg->x;
    user->player->y = egg->y;
    user->player->orientation = egg->orientation;
    user->player->inventory[0] = egg->food;
    user->team_name = egg->team_name;
    user->type = PLAYER;
}

int player_connection(server_t *server, user_t *tmp, team_t *team)
{
    egg_t *egg = server->eggs;

    for (; egg != NULL; egg = egg->next) {
        if (egg->team_name == team->name) {
            team->nb_player--;
            set_user_value(tmp, egg);
            printf("Player connected to %s\n", tmp->team_name);
            send_egg_connection(tmp, egg->id);
            dprintf(tmp->socket, "%d\n", team->nb_player);
            dprintf(tmp->socket, "%d %d\n", server->map->x, server->map->y);
            server->eggs = remove_egg(egg->first, egg->id);
            return 1;
        }
    }
    return 0;
}

static int check_player_connexion(server_t *server, user_t *tmp, team_t *team)
{
    tmp->team_name = team->name;
    if (team->nb_player > 0) {
        player_connection(server, tmp, team);
    } else {
        remove_user(server->wait_list, tmp);
        dprintf(server->sd, "ko\n");
        add_to_list(server->wait_list, tmp);
    }
    return 0;
}

static int add_gui(char *tmp_buffer, server_t *server, user_t *tmp)
{
    egg_t *tmp_egg = NULL;

    if (server->eggs != NULL && server->eggs->first != NULL)
        tmp_egg = server->eggs->first;
    tmp->type = GUI;
    printf("GUI connected at socket %d\n", server->sd);
    print_first_info(server);
    for (; tmp_egg != NULL; tmp_egg = tmp_egg->next) {
        dprintf(server->sd, "enw %d %d %d %d\n", tmp_egg->id,
        get_team_id(server, tmp_egg->team_name) * -1, tmp_egg->x, tmp_egg->y);
    }
    remove_user(server->wait_list, tmp);
    free(tmp_buffer);
    for (user_t *user = tmp->first; user != NULL; user = user->next)
        if (user->type == PLAYER)
            send_new_player(user);
    return 0;
}

int check_team(server_t *server, user_t *tmp)
{
    char *tmp_buffer = read_circular_buffer_string(tmp->cb);

    if (tmp_buffer == NULL)
        return 84;
    if (strcmp(tmp_buffer, "GRAPHIC") == 0)
        return add_gui(tmp_buffer, server, tmp);
    for (team_t *team = server->team; team != NULL; team = team->next)
        if (strcmp(tmp_buffer, team->name) == 0) {
            check_player_connexion(server, tmp, team);
            free(tmp_buffer);
            return 0;
        }
    printf("Unknown team %s\n", tmp_buffer);
    tmp->type = NONE;
    free(tmp_buffer);
    dprintf(server->sd, "ko\n");
    return 0;
}
