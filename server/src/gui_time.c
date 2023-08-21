/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** gui_time
*/

#include <stdio.h>
#include <stdlib.h>

#include "server.h"
#include "str_to_word_array.h"

void time_unit_request(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    dprintf(server->sd, "sgt %d\n", server->map->freq);
}

void time_unit_modif(server_t *server, [[maybe_unused]] user_t *user,
[[maybe_unused]] char *command)
{
    char **tab = str_to_word_array(command, " ");
    char *endptr = NULL;
    int freq = 0;

    if (!tab || !tab[1] || (freq = strtol(tab[1], &endptr, 10)) < 2
    || freq > 1000 || endptr == tab[1]) {
        dprintf(server->sd, "sbp\n");
        return free_word_array(tab);
    }
    server->map->freq = freq;
    dprintf(server->sd, "sst %d\n", server->map->freq);
    free_word_array(tab);
}
