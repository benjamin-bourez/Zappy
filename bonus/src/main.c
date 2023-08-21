/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** main
*/

#include "controller.h"

static int close_client(client_t *client, button_t **buttons,
player_t *player, int error_code)
{
    delete_player(player);
    delete_command_queue(client->queue);
    destroy_tilesmap(client->tilesmap);
    delete_buttons(buttons);
    delete_client(client);
    return (error_code);
}

int main(void)
{
    client_t *client = create_client();
    button_t **buttons = NULL;
    player_t *player = create_inventory();

    if (client == NULL || player == NULL)
        return (close_client(client, buttons, player, 84));
    buttons = generate_buttons(client);
    if (buttons == NULL)
        return (close_client(client, buttons, player, 84));
    if (lauch_client(client))
        return (close_client(client, buttons, player, 84));
    select_client_terminal(client, buttons, player);
    return (close_client(client, buttons, player, 0));
}
