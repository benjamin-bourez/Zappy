/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_gui
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "server.h"
#include "commands_gui.h"

int check_gui(server_t *server, user_t *tmp)
{
    char *tmp_buffer = read_circular_buffer_string(tmp->cb);
    static void (*cmd[9])(server_t *, [[maybe_unused]] user_t *,
    [[maybe_unused]] char *) = {&map_size, &content_tile, &content_map,
    &name_teams, &player_pos, &player_level, &player_inv, &time_unit_request,
    &time_unit_modif};
    static const char *cmd_name[9] = {"msz", "bct", "mct", "tna", "ppo", "plv",
    "pin", "sgt", "sst"};

    if (tmp_buffer == NULL)
        return 84;
    for (int i = 0; i < 9; i++)
        if (strncmp(tmp_buffer, cmd_name[i], strlen(cmd_name[i])) == 0) {
            cmd[i](server, tmp, tmp_buffer);
            free(tmp_buffer);
            return 0;
        }
    dprintf(server->sd, "suc\n");
    free(tmp_buffer);
    tmp->nb_cmd++;
    return 0;
}

void send_to_gui(user_t *user, char *str)
{
    user_t *tmp = user;

    if (user == NULL || str == NULL)
        return;
    while (tmp != NULL) {
        if (tmp->type == GUI)
            dprintf(tmp->socket, "%s\n", str);
        tmp = tmp->next;
    }
}
