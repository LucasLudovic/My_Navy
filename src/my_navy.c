/*
** EPITECH PROJECT, 2024
** navy
** File description:
** my_navy.c
*/

#include <stdlib.h>
#include <signal.h>
#include "my_macros.h"
#include "connection.h"
#include "gameboard.h"

int my_navy(int argc, char **argv)
{
    player_t *player = NULL;

    player = malloc(sizeof(player_t));
    if (player == NULL)
        return FAILURE;
    player->id = argc - 1;
    display_pid(player);
    if (PLAYER1) {
        player->signal_send = SIGUSR1;
        if (wait_connection(player) == FAILURE)
            return FAILURE;
    }
    if (PLAYER2) {
        player->signal_send = SIGUSR2;
        if (request_connection(argv[1]) == FAILURE)
            return FAILURE;
    }
    if (display_user_gameboard(player) == FAILURE)
        return FAILURE;
    if (player != NULL)
        free(player);
    return SUCCESS;
}
