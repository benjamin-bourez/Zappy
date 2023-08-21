/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** cmd_manager
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "commands_gui.h"

void reset_cb(circular_buffer_t *cb)
{
    cb->head_buffer = cb->buffer;
    cb->queue_buffer = cb->buffer;
}

static int read_cmd(server_t *server, user_t *user)
{
    int vread = 0;
    char buffer[1024];

    if (!signal_memory(0, 0) && !(vread = read(user->socket, buffer, 1024))) {
        close(user->socket);
        reset_cb(user->cb);
        server->nb_client--;
        user->socket = 0;
        if (user->type == PLAYER)
            send_player_death(user);
        user->type = NONE;
        remove_user(server->wait_list, user);
        return (1);
    }
    buffer[vread] = '\0';
    if (user->cb != NULL && user->nb_cmd < 10)
        for (int i = 0; i < vread; i++)
            add_to_buffer(buffer[i], user->cb);
    return (0);
}

static int do_cmd(server_t *server, user_t *tmp)
{
    if (FD_ISSET(server->sd , &server->readfds)) {
        if (read_cmd(server, tmp) == 1) {
            tmp = tmp->next;
            return 1;
        }
    }
    if (tmp->type == PLAYER)
        return check_player(server, tmp);
    if (tmp->type == GUI)
        return check_gui(server, tmp);
    if (tmp->type == NONE)
        return check_team(server, tmp);
    if (signal_pipe(0, 0) == 1) {
        close(tmp->socket);
        tmp->socket = 0;
    }
    return 0;
}

void check_cmd(server_t *server, user_t *user)
{
    user_t *tmp = user;

    if (signal_memory(0, 0))
        return;
    while (tmp != NULL) {
        server->sd = tmp->socket;
        if (signal_memory(0, 0) == 0 && do_cmd(server, tmp) == 1)
            continue;
        tmp->first = user;
        tmp = tmp->next;
        signal_pipe(0, 2);
    }
}
