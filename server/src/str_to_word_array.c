/*
** EPITECH PROJECT, 2023
** B-NWP-400-TLS-4-1-myteams-benjamin.bourez
** File description:
** str_to_word_array
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int count_words(char *str, char *delim)
{
    int count = 0;

    for (int j = 0; str[j]; j++) {
        for (int i = 0; delim[i]; i++)
            count += (str[j] == delim[i]);
    }
    return count + 1;
}

int tab_len(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return 0;
    for (; tab[i] != NULL; i++);
    return i;
}

void free_word_array(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}

char **str_to_word_array(char *str, char *delim)
{
    char *dup = strdup(str);
    char *origin = dup;
    int len = count_words(dup, delim);
    char **tab = malloc(sizeof(char *) * (len + 1));
    char *token = strsep(&dup, delim);
    int i = 0;

    while (token != NULL) {
        tab[i] = strdup(token);
        token = strsep(&dup, delim);
        i++;
    }
    tab[i] = NULL;
    free(origin);
    if (strcmp(str, "") == 0) {
        free_word_array(tab);
        return NULL;
    }
    return tab;
}
