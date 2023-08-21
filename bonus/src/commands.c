/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** commands
*/

#include <stdio.h>

#include "controller.h"

int forward([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Forward\n");
    add_command(client->queue, "Forward");
    return 0;
}

int left([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Left\n");
    add_command(client->queue, "Left");
    return 0;
}

int right([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Right\n");
    add_command(client->queue, "Right");
    return 0;
}

int look([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Look\n");
    add_command(client->queue, "Look");
    return 0;
}

int inventory([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Inventory\n");
    add_command(client->queue, "Inventory");
    return 0;
}
