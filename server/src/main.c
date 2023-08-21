/*
** EPITECH PROJECT, 2023
** B-YEP-400-TLS-4-1-zappy-quentin.challon
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "server.h"

static void signal_handler(int signum)
{
    if (signum == SIGINT)
        signal_memory(1, 1);
    if (signum == SIGPIPE)
        signal_pipe(1, 1);
}

static int free_error(server_t *server, user_t *user, timeout_t *timeout)
{
    user_t *tmp = user;

    destroy_server(server);
    while (user != NULL) {
        tmp = user->next;
        destroy_user(user);
        user = tmp;
    }
    if (timeout != NULL)
        free(timeout);
    return (84);
}

static int free_not_error(server_t *server, user_t *user, timeout_t *timeout)
{
    user_t *tmp = user;

    destroy_server(server);
    while (user != NULL) {
        tmp = user->next;
        destroy_user(user);
        user = tmp;
    }
    if (timeout != NULL)
        free(timeout);
    return (0);
}

int main(int ac, char **av)
{
    server_t *server = init_server();
    user_t *user = init_user(NULL);
    timeout_t *timeout = create_timeout();

    srand(time(NULL));
    if (server == NULL || user == NULL || timeout == NULL)
        return free_error(server, user, timeout);
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);
    if (getargs(ac, av, server, 0) == 1)
        return free_not_error(server, user, timeout);
    if (verif_args(server) == 84 || start_server(server) == 84 ||
    generate_objects(server->map) == NULL)
        return free_error(server, user, timeout);
    while (signal_memory(0, 0) == 0) {
        set_fd(server, user, timeout);
        accept_user(server, user);
        check_cmd(server, user);
    }
    return free_not_error(server, user, timeout);
}
