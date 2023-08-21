/*
** EPITECH PROJECT, 2023
** client_controller
** File description:
** str_to_word_array
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"

int nbr_words(char *str, char *delim)
{
    int i = 1;
    int nbr_words = (strchr(delim, str[0])) ? 0 : 1;

    while (str[i] != '\0') {
        if (!strchr(delim, str[i - 1]) && strchr(delim, str[i]))
            nbr_words++;
        i++;
    }
    return (nbr_words);
}

char **my_str_to_word_array(char *str, char *delim)
{
    char **array = malloc(sizeof(char *) * (nbr_words(str, delim) + 1));
    char *token = NULL;
    int i = 0;

    if (array == NULL || str == NULL || delim == NULL)
        return (NULL);
    token = strtok(str, delim);
    while (token != NULL) {
        array[i] = strdup(token);
        token = strtok(NULL, delim);
        i++;
    }
    array[i] = NULL;
    return (array);
}

int free_array(char **array)
{
    int i = 0;

    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
    free(array);
    return (0);
}
