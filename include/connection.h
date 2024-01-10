/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** Player manager
*/

#ifndef CONNECTION_H_
    #define CONNECTION_H_
    #include "player.h"

int wait_connection(void);
void display_pid(player_t *player);
int request_connection(char const *pid_str);

#endif
