/*
** EPITECH PROJECT, 2024
** Gameloop
** File description:
** Header for the gameloop function
*/

#ifndef GAMELOOP_H_
    #define GAMELOOP_H_
    #define INCREMENT 0
    #define SWITCH_STATE 1
    #define GET_VALUE 2
    #include "my_macros.h"
    #include "player.h"

int loop(player_t *player);
int retrieve_ping(int increment);
void handle_signal(int signal, UNUSED siginfo_t *info, UNUSED void *context);

#endif
