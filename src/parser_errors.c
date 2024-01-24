/*
** EPITECH PROJECT, 2024
** navy
** File description:
** parser_errors.c
*/

#include "my_macros.h"
#include "my_navy.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static
int add_boat_vertical_inferior(player_t *player, char *const *map, char nb,
    int i)
{
    for (int j = (map[i][2] - 'A'); j != (map[i][5] - 'A'); j += 1) {
        if (player->map[j][map[i][3] - '1'] != '.' &&
            player->map[j][map[i][3] - '1'] != nb) {
            return display_error("Boat supperpose\n");
        }
        player->map[j][map[i][3] - '1'] = nb;
    }
    return SUCCESS;
}

static
int add_boat_vertical_superior(player_t *player, char *const *map, char nb,
    int i)
{
    for (int j = (map[i][5] - 'A'); j != (map[i][2] - 'A'); j -= 1) {
        if (player->map[j][map[i][3] - '1'] != '.' &&
            player->map[j][map[i][3] - '1'] != nb) {
            return display_error("Boat supperpose\n");
        }
        player->map[j][map[i][3] - '1'] = nb;
    }
    return SUCCESS;
}

static
int link_numbers_vertical(char *const *map, player_t *player, char nb,
    int i)
{
    if (map[i][2] <= map[i][5])
        if (add_boat_vertical_inferior(player, map, nb, i) == FAILURE)
            return FAILURE;
    if (map[i][2] >= map[i][5])
        if (add_boat_vertical_superior(player, map, nb, i) == FAILURE)
            return FAILURE;
    return SUCCESS;
}

static
int add_boat_horizontal_inferior(player_t *player, char *const *map, char nb,
    int i)
{
    for (int j = (map[i][3] - '1'); j != (map[i][6] - '1'); j += 1) {
        if (player->map[map[i][2] - 'A'][j] != '.' &&
            player->map[map[i][2] - 'A'][j] != nb) {
            return display_error("Boat supperpose\n");
        }
        player->map[map[i][2] - 'A'][j] = nb;
    }
    return SUCCESS;
}

static
int add_boat_horizontal_superior(player_t *player, char *const *map, char nb,
    int i)
{
    for (int j = (map[i][6] - '1'); j != (map[i][3] - '1'); j += 1) {
        if (player->map[map[i][2] - 'A'][j] != '.' &&
            player->map[map[i][2] - 'A'][j] != nb) {
            return display_error("Boat supperpose\n");
        }
        player->map[map[i][2] - 'A'][j] = nb;
    }
    return SUCCESS;
}

static
int link_numbers_horizontal(char *const *map, player_t *player, char nb,
    int i)
{
    if (map[i][3] <= map[i][6])
        if (add_boat_horizontal_inferior(player, map, nb, i) == FAILURE)
            return FAILURE;
    if (map[i][3] >= map[i][6])
        if (add_boat_horizontal_superior(player, map, nb, i) == FAILURE)
            return FAILURE;
    return SUCCESS;
}

static
int check_boat_positions(char **map, int i)
{
    if (map[i][2] < 'A' || map[i][2] > 'H' || map[i][5] < 'A' ||
        map[i][5] > 'H')
        return display_error("Wrong column in script\n");
    if (map[i][2] != map[i][5] && map[i][3] != map[i][6])
        return display_error("Impossible boat\n");
    if ((map[i][2] == map[i][5] &&
        (abs(map[i][6] - map[i][3]) != map[i][0] - '0' - 1)) ||
        ((map[i][3] == map[i][6]) &&
        abs(map[i][2] - map[i][5]) != map[i][0] - '0' - 1)) {
        return display_error("Wrong size of boat\n");
    }
    return SUCCESS;
}

int check_map(char **map)
{
    if (map == NULL)
        return FAILURE;
    for (int i = 0; map[i] != NULL; i += 1) {
        if (my_strlen(map[i]) != 7 && my_strlen(map[i]) != 0)
            return display_error("Wrong values\n");
        if (my_strlen(map[i]) == 0) {
            map[i] = NULL;
            free(map[i]);
            continue;
        }
        if (map[i][1] != ':' || map[i][4] != ':' || map[i][7] != '\0')
            return display_error("Wrong separator\n");
        if (map[i][0] < '0' || map[i][0] > '8' || map[i][3] < '0' ||
            map[i][3] > '8' || map[i][6] < '0' || map[i][6] > '8')
            return display_error("Wrong line in script\n");
        if (check_boat_positions(map, i) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}

int link_map(player_t *player, char **map, char nb, int i)
{
    if (map[i][2] != map[i][5]) {
        if (link_numbers_vertical(map, player, nb, i) == FAILURE)
            return FAILURE;
    }
    if (map[i][3] != map[i][6]) {
        if (link_numbers_horizontal(map, player, nb, i) == FAILURE)
            return FAILURE;
    }
    return SUCCESS;
}
