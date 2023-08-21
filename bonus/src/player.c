/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** player_t
*/

#include<stdlib.h>
#include <stdio.h>

#include "controller.h"

static const sfVector2f object_pos[7] = {
    {500, 960},
    {620, 960},
    {740, 960},
    {860, 960},
    {978, 960},
    {1102, 960},
    {1222, 965}
};

static int display_inventory_quantity(sfml_tools_t *sfml,
player_t *player)
{
    char text[4] = {0};
    sfVector2f pos = {500, 960};

    for (int i = 0; i < 7; i++) {
        pos = object_pos[i];
        pos.x += 40;
        pos.y += 40;
        sprintf(text, "%d", player->nbr_objects[i]);
        sfText_setString(sfml->text, text);
        sfText_setPosition(sfml->text, pos);
        sfRenderWindow_drawText(sfml->window, sfml->text, NULL);
    }
    return (0);
}

int display_inventory(player_t *player, client_t *client)
{
    sfVector2f pos = {490, 952};
    sfml_tools_t *sfml = client->sfml;

    for (sprites_t i = 0; i < 7; i++) {
        sfSprite_setPosition(sfml->sprite, pos);
        if (player->actual == i + 3)
            sfSprite_setTexture(sfml->sprite, sfml->texture[CASE_HOVER],
            sfTrue);
        else
            sfSprite_setTexture(sfml->sprite, sfml->texture[CASE], sfTrue);
        sfRenderWindow_drawSprite(sfml->window, sfml->sprite, NULL);
        pos.x += 120;
    }
    for (int i = 0; i < 7; i++)
        if (player->nbr_objects[i] != 0) {
            sfSprite_setPosition(sfml->sprite, object_pos[i]);
            sfSprite_setTexture(sfml->sprite, sfml->texture[i + 3], sfTrue);
            sfRenderWindow_drawSprite(sfml->window, sfml->sprite, NULL);
        }
    return (display_inventory_quantity(sfml, player));
}

player_t *create_inventory(void)
{
    player_t *player = malloc(sizeof(player_t));

    if (!player)
        return (NULL);
    for (int i = 0; i < 7; i++)
        player->nbr_objects[i] = 0;
    player->nbr_objects[0] = 10;
    player->actual = FOOD;
    return (player);
}

int delete_player(player_t *player)
{
    if (!player)
        return 84;
    free(player);
    return 0;
}
