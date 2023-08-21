/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** inventory
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controller.h"

static int get_nbr(char *buffer)
{
    int nbr = 0;

    for (int i = 0; buffer[i]; i++) {
        nbr = atoi(buffer + i);
        if (nbr != 0)
            return (nbr);
    }
    return (0);
}

int get_inventory([[maybe_unused]]client_t *client, char *buffer,
player_t *player)
{
    char *response = NULL;

    if (strcmp(buffer, "ko\n") == 0)
        return (0);
    response = strtok(buffer, ",");
    if (response == NULL)
        return (84);
    for (int i = 0; response != NULL && i < 7; i++) {
        player->nbr_objects[i] = get_nbr(response);
        response = strtok(NULL, ",");
    }
    return (0);
}
