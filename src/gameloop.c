/*
** EPITECH PROJECT, 2024
** Gameloop
** File description:
** Header for the gameloop function
*/

#include <signal.h>
#include <unistd.h>
#include "my.h"
#include "gameloop.h"
#include "gameboard.h"
#include "my_macros.h"
#include "player.h"
#include "my_navy.h"
#include "attack.h"
#include "defense.h"

int retrieve_ping(int increment)
{
    static int number_of_ping = 0;
    static int state_changed = 0;

    if (increment == RESET_STATE) {
        state_changed = 0;
        return SUCCESS;
    }
    if (increment == RESET_PING) {
        number_of_ping = 0;
        return SUCCESS;
    }
    if (state_changed == 1) {
        state_changed = 0;
        return END_RETRIEVE;
    }
    if (increment == INCREMENT)
        number_of_ping += 1;
    if (increment == GET_VALUE)
        return number_of_ping;
    if (increment == SWITCH_STATE) {
        state_changed += 1;
        return END_RETRIEVE;
    }
    return SUCCESS;
}

void handle_signal(int signal, UNUSED siginfo_t *info, UNUSED void *context)
{
    if (signal == SIGUSR2)
        retrieve_ping(SWITCH_STATE);
    if (signal == SIGUSR1)
        retrieve_ping(INCREMENT);
}

int loop(player_t *player)
{
    int game_on = TRUE;

    while (game_on) {
        if (display_user_gameboard(player) == FAILURE)
            return destroy_end(player);
        if (player->my_turn == TRUE) {
            if (play_turn(player) == FAILURE)
                return FAILURE;
        } else {
            my_putstr("waiting for enemy's attack...\n");
            if (receive_attack(player) == FAILURE)
                return FAILURE;
        }
        usleep(1000);
    }
    return SUCCESS;
}
