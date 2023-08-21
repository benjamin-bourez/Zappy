/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** client_destruction
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "controller.h"

int delete_client(client_t *client)
{
    if (client == NULL)
        return 84;
    if (client->ip != NULL)
        free(client->ip);
    if (client->fd != 0)
        close(client->fd);
    if (client->sfml)
        destroy_sfml_tools(client->sfml);
    free(client);
    return (0);
}
