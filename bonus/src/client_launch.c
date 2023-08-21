/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** client_launch
*/

#include <arpa/inet.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "controller.h"

int lauch_client(client_t *client)
{
    struct sockaddr_in s_in;

    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->fd == -1)
        return (84);
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(client->port);
    s_in.sin_addr.s_addr = inet_addr(client->ip);
    if (connect(client->fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
        return (84);
    printf("Connected\n");
    return (0);
}
