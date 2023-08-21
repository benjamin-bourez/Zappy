/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** client_t
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "controller.h"

int set_default_parameters(client_t *client)
{

    client->fd = 0;
    client->port = 4242;
    client->tilesmap = NULL;
    client->last_command = NULL;
    client->state = WAITING_WELCOME;
    client->map_size[0] = 10;
    client->map_size[1] = 10;
    return 0;
}

client_t *create_client(void)
{
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return (NULL);
    set_default_parameters(client);
    client->ip = strdup("127.0.0.1");
    if (client->ip == NULL) {
        free(client);
        return (NULL);
    }
    client->queue = create_command_queue();
    client->sfml = load_sfml_tools();
    if (!client->sfml || !client->queue) {
        delete_client(client);
        return NULL;
    }
    return (client);
}
