/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** display_commads
*/

#include "controller.h"

static int display_no_command(client_t *client)
{
    sfVector2f pos = {50, 30};

    sfText_setString(client->sfml->text, "No command");
    sfText_setPosition(client->sfml->text, pos);
    sfRenderWindow_drawText(client->sfml->window, client->sfml->text, NULL);
    return 0;
}

int display_last_command(client_t *client)
{
    sfVector2f pos = {0, 0};

    sfText_setColor(client->sfml->text, sfWhite);
    sfText_setString(client->sfml->text, "Waiting response for: ");
    sfText_setPosition(client->sfml->text, pos);
    sfRenderWindow_drawText(client->sfml->window, client->sfml->text, NULL);
    if (client->last_command == NULL)
        return display_no_command(client);
    pos = (sfVector2f){50, 30};
    sfText_setString(client->sfml->text, client->last_command);
    sfText_setPosition(client->sfml->text, pos);
    sfRenderWindow_drawText(client->sfml->window, client->sfml->text, NULL);
    return 0;
}
