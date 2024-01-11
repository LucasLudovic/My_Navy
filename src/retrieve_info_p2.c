/*
** EPITECH PROJECT, 2024
** navy
** File description:
** retrieve_info.c
*/

#include "my_macros.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

static void check_linebreak(char **map, int y, int i)
{
    if (map[y][i] == '\n')
        map[y][i] = '\0';
}

static int delete_linebreak(char **map)
{
    if (map == NULL)
        return FAILURE;
    for (int y = 0; map[y] != NULL; y += 1)
        for (int i = 0; map[y][i] != '\0'; i += 1)
            check_linebreak(map, y, i);
    return SUCCESS;
}

static int assign_map(char const **av, char **map)
{
    FILE *file = fopen(av[2], "r");
    char *buff = NULL;
    size_t len = 0;
    ssize_t end_file = 1;
    int i = 0;

    while (end_file > 0) {
        end_file = getline(&buff, &len, file);
        map[i] = my_strdup(buff);
        i += 1;
    }
    map[i - 1] = NULL;
    if (buff != NULL)
        free(buff);
    if (file != NULL)
        fclose(file);
    return SUCCESS;
}

char **retrieve_info_p2(char const **av)
{
    FILE *file = fopen(av[2], "r");
    char *buff = NULL;
    size_t len = 0;
    ssize_t end_file = 1;
    int count = 0;
    char **map = NULL;

    if (file == NULL)
        return NULL;
    while (end_file > 0) {
        end_file = getline(&buff, &len, file);
        count += 1;
        }
    map = malloc(sizeof(char *) * count + 1);
    assign_map(av, map);
    delete_linebreak(map);
    if (buff != NULL)
        free(buff);
    fclose(file);
    printf("map = %s\n", map[0]);
    return map; //penser à free la map
}
