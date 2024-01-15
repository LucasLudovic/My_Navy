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

static int count_boat(char **map)
{
    int i = 0;

    while (map[i] != NULL)
        i += 1;
    return i;
}

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

int transform_map(char **map, player_t *player)
{
    char **info = NULL;
    char nb = 0;

    if (map == NULL)
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
    my_show_word_array(player->map);
    return SUCCESS;
}
