/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** connect
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

bool check_number(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return false;
    return true;
}

void connect(int number, char *team)
{
    char cmd[100] = {0};

    system("mkdir -p log");
    for (int i = 0; i < number; i++) {
        sprintf(cmd, "./zappy_ai -n %s > log/ai_%d.log", team, i + 1);
        if (fork() == 0) {
            printf("AI %d connected\n", i + 1);
            execl("/bin/sh", "sh", "-c", cmd, NULL);
            exit(0);
        }
        usleep(100000);
    }
}

int main(int ac, char **av)
{
    int number = 0;
    char *team = NULL;

    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        printf("USAGE: ./connecter -n number -t team\n");
        return 0;
    }
    if (ac != 5)
        return 84;
    if (strcmp(av[1], "-n") == 0 && check_number(av[2]) && strcmp(av[3], "-t")
    == 0) {
        number = atoi(av[2]);
        team = av[4];
    } else
        return 84;
    if (number < 1)
        return 84;
    connect(number, team);
    return 0;
}
