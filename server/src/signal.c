/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** signal
*/

int signal_memory(int flag, int value)
{
    static int status = 0;

    if (flag == 1)
        status = value;
    return (status);
}

int signal_pipe(int flag, int value)
{
    static int status = 0;

    if (flag == 1)
        status = value;
    if (flag == 2) {
        value = status;
        status = 0;
        return (value);
    }
    return (status);
}
