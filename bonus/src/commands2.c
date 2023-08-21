/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** commands2
*/

#include <stdio.h>

#include "controller.h"

int take_object(button_t *this, client_t *client)
{
    dprintf(client->fd, "Take %s\n", this->name);
    add_command(client->queue, "Take");
    return 0;
}

int set_object(button_t *this, client_t *client)
{
    dprintf(client->fd, "Set %s\n", this->name);
    add_command(client->queue, "Set");
    return 0;
}

int incantation([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Incantation\n");
    add_command(client->queue, "Incantation");
    return 0;
}

int fork_client([[maybe_unused]]button_t *this, client_t *client)
{
    dprintf(client->fd, "Fork\n");
    add_command(client->queue, "Fork");
    return 0;
}
