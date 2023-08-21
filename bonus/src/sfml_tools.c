/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** sfml_tools
*/

#include <stdlib.h>
#include <stdio.h>

#include "controller.h"

int destroy_sfml_tools(sfml_tools_t *tools)
{
    if (tools->sprite)
        sfSprite_destroy(tools->sprite);
    if (tools->font)
        sfFont_destroy(tools->font);
    if (tools->window) {
        sfRenderWindow_close(tools->window);
        sfRenderWindow_destroy(tools->window);
    }
    if (tools->text) {
        sfText_destroy(tools->text);
    }
    if (tools->texture) {
        for (int i = 0; tools->texture[i]; i++)
            sfTexture_destroy(tools->texture[i]);
        free(tools->texture);
    }
    free(tools);
    return 0;
}

static sfTexture *load_texture(char *path)
{
    sfTexture *texture;

    texture = sfTexture_createFromFile(path, NULL);
    if (texture == NULL)
        return (NULL);
    return (texture);
}

static int load_all_textures(sfml_tools_t *tools)
{
    char path[64] = {0};
    tools->texture = malloc(sizeof(sfTexture *) * 27);

    if (tools->texture == NULL)
        return (84);
    for (int i = 0; i < 26; i++) {
        sprintf(path, "assets/images/sprite_%d.png", i);
        tools->texture[i] = load_texture(path);
        if (tools->texture[i] == NULL)
            return 84;
    }
    tools->texture[26] = NULL;
    return 0;
}

sfml_tools_t *load_sfml_tools(void)
{
    sfml_tools_t *tools = malloc(sizeof(sfml_tools_t));

    if (tools == NULL)
        return NULL;
    tools->sprite = sfSprite_create();
    tools->font = sfFont_createFromFile("assets/ttf/PixelifySans-Black.ttf");
    tools->window = sfRenderWindow_create((sfVideoMode){1920, 1080, 32},
    "player_controller", sfFullscreen , NULL);
    tools->text = sfText_create();
    if (!tools->sprite || !tools->font || !tools->window || !tools->text ||
    load_all_textures(tools)) {
        destroy_sfml_tools(tools);
        return NULL;
    }
    sfRenderWindow_setFramerateLimit(tools->window, 60);
    sfSprite_setScale(tools->sprite, (sfVector2f){0.5, 0.5});
    sfText_setFont(tools->text, tools->font);
    return tools;
}
