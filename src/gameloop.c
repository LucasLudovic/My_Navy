/*
** EPITECH PROJECT, 2024
** Gameloop
** File description:
** Header for the gameloop function
*/

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

    if (increment == SWITCH_STATE)
        number_of_ping = 0;
    if (increment == GET_VALUE)
        return number_of_ping;
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
    int received_signal = NO_SIGNAL;

    if (player == NULL)
        return FAILURE;
    if (init_sigaction(&sig_action, handle_signal) == FAILURE)
        return FAILURE;
    return SUCCESS;
}

int send_attack(player_t *player, char case_letter, char case_number)
{
    int ping_letter = case_letter - 'A';
    int ping_number = case_number - '1';

    usleep(1000);
    for (int i = 0; i < ping_letter; i += 1) {
        if (kill(player->enemy_pid, player->signal_send) == -1)
            return FAILURE;
        usleep(1000);
    }
    if (kill(player->enemy_pid, player->signal_stop) == -1)
        return FAILURE;
    for (int i = 0; i < ping_number; i += 1) {
        if (kill(player->enemy_pid, player->signal_send) == -1)
            return FAILURE;
        usleep(1000);
    }
    if (kill(player->enemy_pid, player->signal_stop) == -1)
        return FAILURE;
    return SUCCESS;
}

static
int play_turn(player_t *player)
{
    char buff[3] = "zz";

    if (player == NULL)
        return FAILURE;
    my_putstr("attack : ");
    if (read(STDIN_FILENO, buff, 3) == -1)
        return FAILURE;
    if (buff[2] != '\n')
        return FAILURE;
    buff[2] = '\0';
    if ((buff[0] < 'A' || buff[0] > 'H') ||
        (buff[1] < '1' || buff[1] > '8'))
        return FAILURE;
    my_putstr(buff);
    send_attack(player, buff[0], buff[1]);
    return SUCCESS;
}

static
int respond_to_enemy(player_t *player)
{
    //add data
    return SUCCESS;
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
            if (respond_to_enemy(player) == FAILURE)
                return FAILURE;
        }
        sleep(1);
        break;
    }
    return SUCCESS;
}
