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

static
void handle_signal(int signal, UNUSED siginfo_t *info, UNUSED void *context)
{
    if (signal == SIGUSR2)
        retrieve_ping(SWITCH_STATE);
    if (signal == SIGUSR1)
        retrieve_ping(INCREMENT);
}

static
int respond_hit(player_t *player, int is_hit, int received_number, int received_letter)
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
int respond_to_attack(player_t *player, int received_number, int received_letter)
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
                my_putstr(": ");
            }
            retrieve_ping(RESET_PING);
        }
    }
    return respond_to_attack(player, received_number, received_letter);
}

static
int get_hit_enemy(player_t *player, int ping_letter, int ping_number)
{
    struct sigaction sig_action;

    retrieve_ping(RESET_PING);
    retrieve_ping(RESET_STATE);
    if (init_sigaction(&sig_action, handle_signal) == FAILURE)
        return FAILURE;
    if (sigaction(SIGUSR1, &sig_action, NULL) == -1)
        return display_error("Error setting SIGUSR1\n");
    if (sigaction(SIGUSR2, &sig_action, NULL) == -1)
        return display_error("Error setting SIGUSR2\n");
    pause();
    retrieve_ping(RESET_STATE);
    if (retrieve_ping(GET_VALUE) == 0) {
        my_putstr("missed\n");
        player->enemy_map[ping_number][ping_letter] = 'o';
    } else {
        my_putstr("hit\n");
        player->enemy_map[ping_number][ping_letter] = 'x';
    }
    retrieve_ping(RESET_PING);
    retrieve_ping(RESET_STATE);
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
    return get_hit_enemy(player, buff[0] - 'A', buff[1] - '1');
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
