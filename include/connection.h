/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** Player manager
*/

#ifndef CONNECTION_H_
    #define CONNECTION_H_
    #include "player.h"

void display_pid(player_t *player);
int connect_player(player_t *player, int argc, char **argv);
int init_sigaction(struct sigaction *sig_action);

#endif
