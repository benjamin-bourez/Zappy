/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** manage_sfml_inputs
*/

#include <stdio.h>

#include "controller.h"

static int known_code[7] = {
    sfKeyNum1,
    sfKeyNum2,
    sfKeyNum3,
    sfKeyNum4,
    sfKeyNum5,
    sfKeyNum6,
    sfKeyNum7
};

static int full_screen(client_t *client)
{
    sfVideoMode mode = {1920, 1080, 32};
    static bool is_fullscreen = false;

    sfRenderWindow_destroy(client->sfml->window);
    if (is_fullscreen) {
        client->sfml->window = sfRenderWindow_create(mode, "Zappy",
        sfFullscreen, NULL);
        is_fullscreen = false;
    } else {
        client->sfml->window = sfRenderWindow_create(mode, "Zappy",
        sfClose, NULL);
        is_fullscreen = true;
    }
    return (0);
}

static int manage_keyboard_event(sfEvent event, player_t *player,
client_t *client)
{
    for (int i = 0; i < 7; i++)
        if (known_code[i] == event.key.code)
            player->actual = ARROW_FORWARD + i + 3;
    switch (event.key.code) {
        case sfKeyEscape:
            return (1);
        case sfKeyF11:
            return full_screen(client);
        case sfKeyQuote:
            player->actual = LINEMATE;
            break;
        case 56:
            player->actual = PHIRAS;
            break;
        default:
            break;
    }
    return 0;
}

static int manage_mouse_pressed(client_t *client, button_t **buttons,
sfEvent event)
{
    for (int i = 0; buttons[i]; i++) {
        if (buttons[i]->is_pressed(buttons[i], event, client)) {
            printf("Button %s pressed\n", buttons[i]->name);
            buttons[i]->pressed(buttons[i], client);
        }
    }
    manage_tile_hover(client, event);
    return (0);
}

static int manage_wheel_move(player_t *player,
sfEvent event)
{
    int temp = player->actual;

    if (event.type != sfEvtMouseWheelScrolled)
        return (0);
    temp -= 3;
    if (event.mouseWheelScroll.delta == 1.0)
        temp -= 1;
    if (event.mouseWheelScroll.delta == -1.0)
        temp = (temp + 1) % 7;
    if (temp < 0)
        temp += 7;
    temp += 3;
    player->actual = temp;
    return (0);
}

int manage_sfml_inputs(client_t *client, button_t **buttons,
player_t *player)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(client->sfml->window, &event)) {
        if (event.type == sfEvtClosed)
            return (1);
        if (event.type == sfEvtKeyPressed &&
        manage_keyboard_event(event, player, client))
            return (1);
        manage_mouse_pressed(client, buttons, event);
        manage_wheel_move(player, event);
    }
    return (0);
}
