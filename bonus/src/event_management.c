/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** event_management
*/

#include "controller.h"

static bool is_tile_hover(tile_t *tile, sfEvent event)
{
    sfVector2i mouse_pos = {event.mouseMove.x, event.mouseMove.y};
    sfVector2f tile_pos = {tile->x, tile->y};
    sfVector2f tile_size = {tile->size, tile->size};

    if (mouse_pos.x >= tile_pos.x && mouse_pos.x <= tile_pos.x + tile_size.x
    && mouse_pos.y >= tile_pos.y && mouse_pos.y <= tile_pos.y + tile_size.y)
        return (true);
    return (false);
}

int manage_tile_hover(client_t *client, sfEvent event)
{
    tilesmap_t *tilesmap = NULL;
    tile_t *tile = NULL;

    if (!client || !client->tilesmap || client->state < CLIENT_PLAYING)
        return (0);
    tilesmap = client->tilesmap;
    for (int i = 0; tilesmap[i]; i++) {
        for (int j = 0; tilesmap[i][j]; j++) {
            tile = tilesmap[i][j];
            tile->is_hover = is_tile_hover(tile, event) ? true : false;
        }
    }
    return (0);
}
