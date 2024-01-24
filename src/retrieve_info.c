/*
** EPITECH PROJECT, 2024
** navy
** File description:
** retrieve_info.c
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "my_macros.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "player.h"
#include "my.h"

static
void check_linebreak(char **map, int y, int i)
{
    if (map[y][i] == '\n')
        map[y][i] = '\0';
}

static
int delete_linebreak(char **map)
{
    if (map == NULL)
        return FAILURE;
    for (int y = 0; map[y] != NULL; y += 1)
        for (int i = 0; map[y][i] != '\0'; i += 1)
            check_linebreak(map, y, i);
    return SUCCESS;
}

static
void close_file(FILE *file, char *buff)
{
    if (buff != NULL)
        free(buff);
    if (file != NULL)
        fclose(file);
}

static
int assign_map(char **argv, char **map, player_t *player)
{
    FILE *file = NULL;
    char *buff = NULL;
    size_t len = 0;
    ssize_t end_file = 1;
    int i = 0;

    if (PLAYER1)
        file = fopen(argv[1], "r");
    if (PLAYER2)
        file = fopen(argv[2], "r");
    while (end_file > 0) {
        end_file = getline(&buff, &len, file);
        map[i] = my_strdup(buff);
        i += 1;
    }
    map[i - 1] = NULL;
    close_file(file, buff);
    return SUCCESS;
}

static
char **retrieve_map(char **argv, int count, char **map, player_t *player)
{
    map = malloc(sizeof(char *) * (count + 1));
    assign_map(argv, map, player);
    delete_linebreak(map);
    return map;
}

static
int check_file(char **argv, player_t *player)
{
    int file = -1;

    if (player == NULL || argv == NULL)
        return FAILURE;
    file = open(argv[player->id], O_RDONLY);
    if (file == -1)
        return FAILURE;
    close(file);
    return SUCCESS;
}

static
int check_error_file(player_t *player, char **argv, FILE **file)
{
    if (check_file(argv, player) == FAILURE)
        return FAILURE;
    *file = fopen(argv[player->id], "r");
    if (*file == NULL)
        return FAILURE;
    return SUCCESS;
}

char **retrieve_info(player_t *player, char **argv)
{
    FILE *file = NULL;
    char *buff = NULL;
    size_t len = 0;
    ssize_t end_file = 1;
    int count = 0;
    char **map = NULL;

    if (check_error_file(player, argv, &file) == FAILURE)
        return NULL;
    while (end_file > 0) {
        end_file = getline(&buff, &len, file);
        count += 1;
    }
    if (count <= 1) {
        fclose(file);
        return NULL;
    }
    map = retrieve_map(argv, count, map, player);
    close_file(file, buff);
    return map;
}
