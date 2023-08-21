/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** response_management
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "controller.h"

static int (*response_action[2])(client_t *, char *, player_t *) = {
    &get_inventory,
    &get_look
};

static const char *response[1] = {
    "Inventory"
};

static int send_team_name(client_t *client, char *buffer,
[[maybe_unused]]player_t *inv)
{
    if (strcmp(buffer, "WELCOME\n") == 0) {
        dprintf(client->fd, "Team1\n");
        client->state = WAITING_NBR_CLIENTS;
    }
    return (0);
}

static int get_team_nbr(client_t *client, char *buffer,
[[maybe_unused]]player_t *inv)
{
    if (strcmp(buffer, "ko\n") == 0)
        client->state = WAITING_NBR_CLIENTS;
    else
        client->state = WAITING_MAP_SIZE;
    return (0);
}

static int get_map_size(client_t *client, char *buffer,
[[maybe_unused]]player_t *inv)
{
    char *response = NULL;

    if (strcmp(buffer, "ko\n") == 0) {
        client->state = WAITING_NBR_CLIENTS;
        return (0);
    }
    client->state = CLIENT_PLAYING;
    response = strtok(buffer, " ");
    if (response == NULL)
        return (84);
    client->map_size[0] = atoi(response);
    response = strtok(NULL, " ");
    if (response == NULL)
        return (84);
    client->map_size[1] = atoi(response);
    if (client->map_size[0] == 0 || client->map_size[1] == 0)
        return (84);
    client->tilesmap = generate_tilesmap(client->map_size[0],
    client->map_size[1]);
    return client->tilesmap == NULL ? 84 : 0;
}

static int get_command_playing(client_t *client, char *buffer,
player_t *inv)
{
    if (client->last_command == NULL) {
        write(1, buffer, strlen(buffer));
        return 0;
    }
    for (int i = 0; i < 1; i++)
        if (strcmp(client->last_command, response[i]) == 0) {
            free(client->last_command);
            client->last_command = NULL;
            return (response_action[i](client, buffer, inv));
        }
    write(1, buffer, strlen(buffer));
    return 0;
}

int read_socket(client_t *client, player_t *inv)
{
    int (*response_management[4])(client_t *, char *, player_t *) = {
        &send_team_name, &get_team_nbr, &get_map_size, &get_command_playing};
    char buffer[1024] = {0};
    int read_size = 0;

    read_size = read(client->fd, buffer, 1024);
    if (read_size == 0)
        return (1);
    if (read_size == -1)
        return (84);
    for (state_t i = 0; i < 4; i++)
        if (client->state == i)
            return (response_management[i](client, buffer, inv));
    write(1, buffer, read_size);
    if (strcmp(buffer, "dead\n") == 0)
        return (1);
    return (0);
}
