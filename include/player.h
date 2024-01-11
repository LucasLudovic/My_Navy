/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** Player manager
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

typedef struct player_s {
    int id;
    int enemy_pid;
    int signal_send;
    int signal_stop;
    char **map;
    char **enemy_map;
} player_t;

#endif
