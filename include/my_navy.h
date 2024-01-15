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
char **retrieve_info_p1(player_t *player, char **av);
char **retrieve_info_p2(char **av);
char **retrieve_info_boat(char *info);
int transform_map(char **map, player_t *player);
int destroy_end(player_t *player);

#endif
