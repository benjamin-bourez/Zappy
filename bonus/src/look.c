/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** look
*/

#include "controller.h"

static int is_empty(char *buffer, int *j)
{
    int i = 0;

    for (; buffer[*j] != '\0' && buffer[*j] != ','; (*j)++, i++);
    (*j) += 1;
    return !(i);
}

static sfVector2f get_position(int index, direction_t direction)
{
    int max = -1;
    sfVector2f pos = {0, 0};
    int i = 0;

    for (; i < 10; i++) {
        max += i * 2 + 1;
        if (index <= max) {
            pos = (sfVector2f){i, i - (max - index)};
            break;
        }
    }
    if (direction == NORTH)
        pos.y *= -1;
    if (direction == EAST)
        pos = (sfVector2f){pos.y, pos.x};
    if (direction == SOUTH)
        pos = (sfVector2f){pos.x, pos.y * -1};
    if (direction == WEST)
        pos = (sfVector2f){pos.y * -1, pos.x * -1};
    return pos;
}

int get_look([[maybe_unused]]client_t *client, char *buffer,
player_t *player)
{
    char **look = NULL;
    int j = 0;
    sfVector2f pos = {0, 0};

    if (buffer == NULL)
        return (84);
    buffer += 1;
    look = my_str_to_word_array(buffer, "[],");
    if (look == NULL)
        return (84);
    for (int i = 0; look[i]; i++) {
        if (is_empty(buffer, &j))
            continue;
        pos = get_position(i, player->direction);
        player->pos.x += pos.x;
        player->pos.y += pos.y;
    }
    return 0;
}
