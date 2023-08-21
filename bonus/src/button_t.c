/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** button_t
*/

#include <stdlib.h>
#include <stdio.h>

#include "controller.h"

static const sprites_t button_sprites[] = {
    ARROW_FORWARD,
    ARROW_LEFT,
    ARROW_RIGHT,
    EYE,
    EGG,
    CHEST,
    LEVEL_UP
};

static int (*button_commands[])(button_t *this, client_t *client) = {
    &forward,
    &left,
    &right,
    &look,
    &fork_client,
    &inventory,
    &incantation
};

static const char *button_names[] = {
    "Forward",
    "Left",
    "Right",
    "Look",
    "Fork",
    "Inventory",
    "Incantation"
};

static const sfVector2f button_pos[] = {
    {1675, 830},
    {1540, 960},
    {1800, 960},
    {1800, 780},
    {1550, 780},
    {1670, 960},
    {1680, 700}
};

static bool is_pressed(button_t *this, sfEvent event, client_t *client)
{
    sfVector2i mouse_pos =
    sfMouse_getPositionRenderWindow(client->sfml->window);

    if (event.type == sfEvtMouseButtonPressed &&
        mouse_pos.x >= this->pos.x && mouse_pos.x <= this->pos.x +
        this->size.x && mouse_pos.y >= this->pos.y && mouse_pos.y <=
        this->pos.y + this->size.y)
        return true;
    return false;
}

button_t *create_button(sprites_t type, client_t *client,
int (*pressed)(button_t *this, client_t *client), const char *name)
{
    button_t *button = malloc(sizeof(button_t));
    sfVector2u size;

    button->name = name;
    button->pos = (sfVector2f){0, 0};
    button->texture = client->sfml->texture[type];
    size = sfTexture_getSize(button->texture);
    button->size = (sfVector2u){size.x / 2, size.y / 2};
    button->is_pressed = &is_pressed;
    button->pressed = pressed;
    return (button);
}

int delete_buttons(button_t **buttons)
{
    if (!buttons)
        return 84;
    for (int i = 0; buttons[i]; i++)
        free(buttons[i]);
    free(buttons);
    return 0;
}

int draw_button(button_t *button, client_t *client)
{
    sfSprite_setScale(client->sfml->sprite, (sfVector2f){0.5, 0.5});
    sfSprite_setTexture(client->sfml->sprite, button->texture, sfTrue);
    sfSprite_setPosition(client->sfml->sprite, button->pos);
    sfRenderWindow_drawSprite(client->sfml->window, client->sfml->sprite, NULL);
    return 0;
}

button_t **generate_buttons(client_t *client)
{
    button_t **buttons = malloc(sizeof(button_t *) * 8);

    for (int i = 0; i < 7; i++) {
        buttons[i] = create_button(button_sprites[i], client,
            button_commands[i], button_names[i]);
        if (!buttons[i])
            return NULL;
        buttons[i]->pos = button_pos[i];
    }
    buttons[7] = NULL;
    return buttons;
}
