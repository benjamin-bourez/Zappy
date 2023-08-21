/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** start_server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static int fail_exit(char *str)
{
    puts(str);
    return 84;
}

static int get_ip(void)
{
    char buffer[256];
    char *ip = NULL;
    FILE* command_output = popen("hostname -I", "r");

    if (command_output == NULL) {
        perror("Erreur lors de l'exécution de la commande");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), command_output) != NULL) {
        ip = strtok(buffer, " ");
        printf("Waiting for connections on %s\n", ip);
    }
    pclose(command_output);
    return 0;
}

static void set_adress(server_t *server)
{
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    server->addrlen = sizeof(server->address);
}

int start_server(server_t *server)
{
    if (server->port < 1024 || server->port > 65535)
        return (fail_exit("Port must be between 1024 and 65535"));
    set_adress(server);
    printf("Starting server on port %d\n", server->port);
    get_ip();
    if ((server->master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
        return (fail_exit("socket failed"));
    if (setsockopt(server->master_socket, SOL_SOCKET, SO_REUSEADDR,
    (char *)&server->opt, sizeof(server->opt)) < 0 )
        return (fail_exit("setsockopt failed"));
    if (bind(server->master_socket, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0)
        return (fail_exit("bind failed"));
    if (listen(server->master_socket, 3) < 0)
        return (fail_exit("listen failed"));
    if (!generate_tilesmap(server->map) || !generate_eggs(server))
        return 84;
    server->last_update = 20 / server->map->freq * 1000000;
    return (0);
}
