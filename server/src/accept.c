/*
** EPITECH PROJECT, 2023
** B-NWP-400-TLS-4-1-myteams-benjamin.bourez
** File description:
** accept
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server.h"

static void reset_user(user_t *user)
{
    user->socket = 0;
    user->type = NONE;
    user->team_name = NULL;
    if (user->buffer != NULL) {
        free(user->buffer);
        user->buffer = NULL;
    }
    reset_cb(user->cb);
    user->player->is_incanting = false;
    user->player->time = 0;
    user->player->save_time = 0;
    user->player->last_food_eaten = 0;
    user->player->x = 0;
    user->player->y = 0;
    user->player->level = 1;
    user->player->id = 0;
    user->player->orientation = 1;
}

static void manage_socket(server_t *server, user_t *tmp)
{
    if (server->sd == 0)
        reset_user(tmp);
    if (server->sd > server->max_sd)
        server->max_sd = server->sd;
}

void set_fd(server_t *server, user_t *user, timeout_t *timeout)
{
    user_t *tmp = user;
    long int total_timeout;

    FD_ZERO(&server->readfds);
    FD_SET(server->master_socket, &server->readfds);
    server->max_sd = server->master_socket;
    while (tmp != NULL) {
        server->sd = tmp->socket;
        if (server->sd > 0)
            FD_SET(server->sd, &server->readfds);
        manage_socket(server, tmp);
        tmp = tmp->next;
    }
    total_timeout = update_select(server, user, timeout);
    server->activity
    = select(server->max_sd + 1, &server->readfds, NULL, NULL, timeout);
    update_time(server, user, timeout, total_timeout);
    if ((server->activity < 0) && (errno != EINTR))
        puts("select error");
}

void set_socket(server_t *server, user_t *user)
{
    user_t *tmp = user;

    printf("New connection, socket fd is %d. Number of client connected: %d\n",
    server->new_socket, server->nb_client + 1);
    if (user == NULL) {
        return;
    } else if (tmp->socket == 0) {
        tmp->socket = server->new_socket;
        tmp->player->last_food_eaten = 126.0 / server->map->freq * 1000000;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = init_user(user);
    tmp->player->last_food_eaten = 126.0 / server->map->freq * 1000000;
    tmp->next->socket = server->new_socket;
}

void accept_user(server_t *server, user_t *user)
{
    if (FD_ISSET(server->master_socket, &server->readfds)) {
        if (signal_memory(0, 0) == 0 && (server->new_socket =
        accept(server->master_socket, (struct sockaddr *)&server->address,
        (socklen_t*)&server->addrlen)) < 0)
            return;
        if (server->nb_client > 180) {
            close(server->new_socket);
            server->new_socket = 0;
            printf("Too many client connected\n");
            return;
        }
        if (signal_memory(0, 0) == 0 && dprintf(server->new_socket,
        "WELCOME\n") != (int)strlen("WELCOME\n"))
            return;
        if (server->new_socket > 0) {
            set_socket(server, user);
            server->new_socket = 0;
            server->nb_client++;
        }
    }
}
