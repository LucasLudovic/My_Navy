/*
** EPITECH PROJECT, 2024
** navy
** File description:
** transform_map.c
*/

#include "my_macros.h"
#include "my_navy.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include "parser_errors.h"

static
int create_map(player_t *player)
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
        if (link_map(player, map, nb, i) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}
