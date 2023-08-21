/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** tiles_management
*/

#include <stdlib.h>
#include <string.h>

#include "controller.h"

int display_map(client_t *client)
{
    sfTexture *texture = NULL;
    tile_t *tile = NULL;

    for (int i = 0; client->tilesmap[i] != NULL; i++) {
        for (int j = 0; client->tilesmap[i][j] != NULL; j++) {
            tile = client->tilesmap[i][j];
            texture = (tile->is_hover) ? client->sfml->texture[GRASS_HOVER] :
            client->sfml->texture[GRASS];
            sfSprite_setTexture(client->sfml->sprite, texture, sfTrue);
            sfSprite_setPosition(client->sfml->sprite,
            (sfVector2f){tile->x, tile->y});
            sfSprite_setScale(client->sfml->sprite, tile->scale);
            sfRenderWindow_drawSprite(client->sfml->window,
            client->sfml->sprite, NULL);
        }
    }
    return 0;
}

tile_t *create_tile(void)
{
    tile_t *tile = malloc(sizeof(tile_t));

    if (tile == NULL)
        return (NULL);
    tile->is_hover = false;
    tile->nbr_eggs = 0;
    tile->nbr_players = 0;
    tile->x = 0;
    tile->y = 0;
    tile->size = 0;
    for (int i = 0; i < 7; i++)
        tile->nbr_objects[i] = 0;
    return (tile);
}

int destroy_tilesmap(tilesmap_t *tilesmap)
{
    if (tilesmap == NULL)
        return 0;
    for (int i = 0; tilesmap[i] != NULL; i++) {
        for (int j = 0; tilesmap[i][j] != NULL; j++)
            free(tilesmap[i][j]);
        free(tilesmap[i]);
    }
    free(tilesmap);
    return 0;
}

static int set_tiles_position(tilesmap_t *tilesmap, int width, int height)
{
    sfVector2f scale = {0, 0};
    int max_size = (width > height) ? width : height;
    int desiered_size = 800 / max_size;
    int margin_left = 0;
    int margin_top = 0;

    margin_left = (800 - desiered_size * width) / 2;
    margin_top = (800 - desiered_size * height) / 2;
    scale = (sfVector2f){desiered_size / 95.0, desiered_size / 95.0};
    for (int i = 0; tilesmap[i]; i++) {
        for (int j = 0; tilesmap[i][j]; j++) {
            tilesmap[i][j]->x = 510 + margin_left + j * desiered_size;
            tilesmap[i][j]->y = 100 + margin_top + i * desiered_size;
            tilesmap[i][j]->size = desiered_size;
            tilesmap[i][j]->scale = scale;
        }
    }
    return 0;
}

tilesmap_t *generate_tilesmap(int width, int height)
{
    tilesmap_t *tilesmap = malloc(sizeof(tilesmap_t) * (height + 1));
    int i = 0;
    int j = 0;
    bool stop = false;

    if (tilesmap == NULL)
        return (NULL);
    for (i = 0; i < height; i++) {
        tilesmap[i] = malloc(sizeof(tile_t *) * (width + 1));
        stop = (!tilesmap[i]) ? destroy_tilesmap(tilesmap) + 1 : false;
        for (j = 0; j < width && !stop; j++) {
            tilesmap[i][j] = create_tile();
            stop = (!tilesmap[i][j]) ? destroy_tilesmap(tilesmap) + 1 : false;
        }
        if (stop)
            return (NULL);
        tilesmap[i][j] = NULL;
    }
    tilesmap[i] = NULL;
    return set_tiles_position(tilesmap, width, height) ? NULL : tilesmap;
}
