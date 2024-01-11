/*
** EPITECH PROJECT, 2024
** navy
** File description:
** transfor_map.c
*/

#include "my_macros.h"
#include "my_navy.h"
#include "map_p1.h"
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

int transform_map(char **map)
{
    char **info = NULL;
    map1_t *map_s = NULL;
    if (map == NULL)
        return FAILURE;
    map_s = malloc(sizeof(map1_t) * count_boat(map));
    for (int i = 0; map[i] != NULL; i += 1) {
        info = retrieve_info_boat(map[i]);
        map_s->boat_size = my_strdup(info[0]);
        map_s->boat_intiplace = my_strdup(info[1]);
        map_s->boat_lastplace = my_strdup(info[2]);
    }
    return SUCCESS;
}
