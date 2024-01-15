/*
** EPITECH PROJECT, 2024
** Defense
** File description:
** Handle the defense functions
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "my.h"
#include "gameloop.h"
#include "my_macros.h"
#include "player.h"
#include "connection.h"

static
int respond_hit(player_t *player, int is_hit, int received_number,
    int received_letter)
{
    if (is_hit == TRUE) {
        player->map[received_number][received_letter] = 'x';
        my_putstr("hit\n");
        usleep(1000);
        kill(player->enemy_pid, player->signal_send);
        usleep(1000);
    } else {
        player->map[received_number][received_letter] = 'o';
        my_putstr("missed\n");
        usleep(1000);
        kill(player->enemy_pid, player->signal_stop);
        usleep(1000);
    }
    return SUCCESS;
}

static
int respond_to_attack(player_t *player, int received_number,
    int received_letter)
{
    int is_hit = FALSE;

    if (player == NULL || player->map == NULL)
        return display_error("Unable to use player in response\n");
    if (received_number < 0 || received_letter < 0)
        return display_error("Wrong attack values\n");
    printf("Test : %i-%i\n", received_number, received_letter);
    if (player->map[received_number][received_letter] != '.') {
        is_hit = TRUE;
    }
    return respond_hit(player, is_hit, received_number, received_letter);
}

static
void noname(player_t *player, int *changed_state, int *received_letter,
    int *received_number)
{
    int received_value = 0;

    received_value = retrieve_ping(GET_VALUE);
    if (received_value == END_RETRIEVE) {
        *changed_state += 1;
        if (*changed_state == 1) {
            *received_letter = retrieve_ping(GET_VALUE);
            my_putchar(*received_letter + 'A');
            received_value = 0;
        }
        if (*changed_state == 2) {
            player->my_turn = TRUE;
            *received_number = retrieve_ping(GET_VALUE);
            my_putchar(*received_number + '1');
            my_putstr(": ");
        }
        retrieve_ping(RESET_PING);
    }
}

int receive_attack(player_t *player)
{
    struct sigaction sig_action;
    int received_letter = 0;
    int received_number = 0;
    int changed_state = 0;

    if (player == NULL)
        return FAILURE;
    if (init_sigaction(&sig_action, handle_signal) == FAILURE)
        return FAILURE;
    if (sigaction(SIGUSR1, &sig_action, NULL) == -1)
        return display_error("Error setting SIGUSR1\n");
    if (sigaction(SIGUSR2, &sig_action, NULL) == -1)
        return display_error("Error setting SIGUSR2\n");
    while (changed_state < 2) {
        pause();
        noname(player, &changed_state, &received_letter, &received_number);
    }
    return respond_to_attack(player, received_number, received_letter);
}
