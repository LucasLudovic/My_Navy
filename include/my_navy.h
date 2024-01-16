/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** Function handler for the navy project
*/

#ifndef MY_NAVY_H_
    #define MY_NAVY_H_
    #include "player.h"

int my_navy(int argc, char **argv);
int destroy_end(player_t *player);
char **retrieve_info(player_t *player, char **argv);
int transform_map(char **map, player_t *player);

#endif
