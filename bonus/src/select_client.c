/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** select_client
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "controller.h"

static int get_last_command(client_t *client)
{
    if (client->last_command != NULL)
        return 0;
    if (client->queue == NULL || client->queue->first == NULL)
        return 0;
    client->last_command = get_command(client->queue);
    return 0;
}

static int draw_connextion(client_t *client)
{
    if (client->state >= CLIENT_PLAYING) {
        sfText_setString(client->sfml->text, "Connected");
        sfText_setPosition(client->sfml->text, (sfVector2f){850, 0});
    } else {
        sfText_setString(client->sfml->text, "Not yet connected");
        sfText_setPosition(client->sfml->text, (sfVector2f){800, 0});
    }
    sfRenderWindow_drawText(client->sfml->window, client->sfml->text, NULL);
    return 0;
}

static int draw(client_t *client, button_t **buttons, player_t *player)
{
    sfRenderWindow_clear(client->sfml->window, sfBlack);
    display_last_command(client);
    draw_connextion(client);
    display_inventory(player, client);
    if (client->state >= CLIENT_PLAYING)
        display_map(client);
    for (int i = 0; buttons[i]; i++)
        draw_button(buttons[i], client);
    sfRenderWindow_display(client->sfml->window);
    return (0);
}

int select_client_terminal(client_t *client, button_t **buttons,
player_t *player)
{
    fd_set readfds;
    int error_code = 0;
    struct timeval timeout = {0, 0};

    while (error_code == 0) {
        FD_ZERO(&readfds);
        FD_SET(client->fd, &readfds);
        if (select(client->fd + 1, &readfds, NULL, NULL, &timeout) == -1) {
            perror("select");
            return (84);
        }
        if (FD_ISSET(client->fd, &readfds))
            error_code += read_socket(client, player);
        error_code += manage_sfml_inputs(client, buttons, player);
        get_last_command(client);
        draw(client, buttons, player);
    }
    return (0);
}
