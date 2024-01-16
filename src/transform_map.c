/*
** EPITECH PROJECT, 2024
** navy
** File description:
** transfor_map.c
*/

#include "my_macros.h"
#include "my_navy.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static int create_map(player_t *player)
{
    if (player == NULL)
        return FAILURE;
    player->map = malloc(sizeof(char *) * 9);
    if (player->map == NULL)
        return FAILURE;
    for (int i = 0; i != 8; i += 1) {
        player->map[i] = malloc(sizeof(char) * 9);
        if (player->map[i] == NULL)
            return FAILURE;
    }
    player->map[8] = NULL;
    for (int i = 0; player->map[i] != NULL; i += 1)
        player->map[i][8] = '\0';
    for (int i = 0; player->map[i] != NULL; i += 1)
        for (int j = 0; j < Y_CASE; j += 1)
            player->map[i][j] = '.';
    return SUCCESS;
}

static
void link_numbers_vertical(char *const *map, player_t *player, char nb, int i)
{
    if (map[i][2] <= map[i][5])
        for (int j = (map[i][2] - 'A'); j != (map[i][5] - 'A'); j += 1)
            player->map[j][map[i][3] - '1'] = nb;
    if (map[i][2] >= map[i][5])
        for (int j = (map[i][5] - 'A'); j != (map[i][2] - 'A'); j -= 1)
            player->map[j][map[i][3] - '1'] = nb;
}

static void
link_numbers_horizontal(char *const *map, player_t *player, char nb, int i)
{
    if (map[i][3] <= map[i][6])
        for (int j = (map[i][3] - '1'); j != (map[i][6] - '1'); j += 1)
            player->map[map[i][2] - 'A'][j] = nb;
    if (map[i][3] >= map[i][6])
        for (int j = (map[i][6] - '1'); j != (map[i][3] - '1'); j += 1)
            player->map[map[i][2] - 'A'][j] = nb;
}

static int check_map(char **map)
{
    for (int i = 0; map[i] != NULL; i += 1) {
        if (my_strlen(map[i]) != 7 && my_strlen(map[i]) != 0)
            return FAILURE;
        if (my_strlen(map[i]) == 0) {
            map[i] = NULL;
            free(map[i]);
            continue;
        }
        if (map[i][1] != ':' || map[i][4] != ':' || map[i][7] != '\0')
            return FAILURE;
        if (map[i][0] < '0' || map[i][0] > '8' || map[i][3] < '0' ||
            map[i][3] > '8' || map[i][6] < '0' || map[i][6] > '8')
            return FAILURE;
        if (map[i][2] < 'A' || map[i][2] > 'H' || map[i][5] < 'A' ||
            map[i][5] > 'H')
            return FAILURE;
    }
    return SUCCESS;
}

int transform_map(char **map, player_t *player)
{
    char nb = 0;

    if (map == NULL)
        return FAILURE;
    if (check_map(map) == FAILURE)
        return FAILURE;
    create_map(player);
    for (int i = 0; map[i] != NULL; i += 1) {
        nb = map[i][0];
        player->map[map[i][2] - 'A'][map[i][3] - '1'] = nb;
        player->map[map[i][5] - 'A'][map[i][6] - '1'] = nb;
        if (map[i][2] != map[i][5]) {
            link_numbers_vertical(map, player, nb, i);
        }
        if (map[i][3] != map[i][6]) {
            link_numbers_horizontal(map, player, nb, i);
        }
    }
    return SUCCESS;
}