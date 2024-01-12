/*
** EPITECH PROJECT, 2024
** Gameloop
** File description:
** Header for the gameloop function
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <connection.h>
#include <time.h>
#include "my.h"
#include "gameloop.h"
#include "gameboard.h"
#include "my_macros.h"
#include "player.h"
#include "my_navy.h"

static
int retrieve_ping(int increment)
{
    static int number_of_ping = 0;
    static int state_changed = 0;

    if (state_changed == 1) {
        state_changed = 0;
        return END_RETRIEVE;
    }
    if (increment == GET_VALUE)
        return number_of_ping;
    if (increment == RESET_PING)
        number_of_ping = 0;
    if (increment == SWITCH_STATE) {
        state_changed += 1;
        return END_RETRIEVE;
    }
    if (increment == INCREMENT)
        number_of_ping += 1;
    return SUCCESS;
}

static
void handle_signal(int signal, siginfo_t *info, UNUSED void *context)
{
    if (signal == SIGUSR2)
        retrieve_ping(SWITCH_STATE);
    if (signal == SIGUSR1)
        retrieve_ping(INCREMENT);
}

int receive_attack(player_t *player)
{
    struct sigaction sig_action;
    int received_value = 0;
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
        received_value = retrieve_ping(GET_VALUE);
        if (received_value == END_RETRIEVE) {
            changed_state += 1;
            if (changed_state == 1) {
                received_letter = retrieve_ping(GET_VALUE);
                my_putchar(received_letter + 'A');
                received_value = 0;
            }
            if (changed_state == 2) {
                player->my_turn = TRUE;
                received_number = retrieve_ping(GET_VALUE);
                my_putchar(received_number + '1');
                my_putchar('\n');
            }
            retrieve_ping(RESET_PING);
        }
    }
    return SUCCESS;
}

int send_attack(player_t *player, char case_letter, char case_number)
{
    int ping_letter = case_letter - 'A';
    int ping_number = case_number - '1';

    usleep(1000);
    for (int i = 0; i < ping_letter; i += 1) {
        if (kill(player->enemy_pid, player->signal_send) == -1)
            return display_error("Unable to send the letter case\n");
        usleep(1000);
    }
    if (kill(player->enemy_pid, player->signal_stop) == -1)
        return display_error("Unable to send the change state\n");
    usleep(1000);
    for (int i = 0; i < ping_number; i += 1) {
        if (kill(player->enemy_pid, player->signal_send) == -1)
            return display_error("Unable to send the number case\n");
        usleep(1000);
    }
    if (kill(player->enemy_pid, player->signal_stop) == -1)
        return display_error("Unable to send the end turn\n");
    player->my_turn = FALSE;
    return SUCCESS;
}

static
int play_turn(player_t *player)
{
    char buff[3] = "zz";

    if (player == NULL)
        return FAILURE;
    my_putstr("attack: ");
    if (read(STDIN_FILENO, buff, 3) == -1)
        return display_error("Unable to read the attack\n");
    if (buff[2] != '\n')
        return display_error("Wrong value entered\n");
    buff[2] = '\0';
    if ((buff[0] < 'A' || buff[0] > 'H') ||
        (buff[1] < '1' || buff[1] > '8'))
        return display_error("Wrong attack entered\n");
    if (send_attack(player, buff[0], buff[1]) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

static
int respond_to_enemy(player_t *player)
{
    return receive_attack(player);
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
            if (respond_to_enemy(player) == FAILURE)
                return FAILURE;
        }
        usleep(1000);
    }
    return SUCCESS;
}
