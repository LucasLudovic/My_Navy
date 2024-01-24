/*
** EPITECH PROJECT, 2024
** Attack
** File description:
** Handle the attack functions
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <connection.h>
#include "my.h"
#include "gameloop.h"
#include "my_macros.h"
#include "player.h"

static
void reset_value(void)
{
    retrieve_ping(RESET_PING);
    retrieve_ping(RESET_STATE);
}

static
int get_hit_enemy(player_t *player, int ping_letter, int ping_number)
{
    struct sigaction sig_action;

    reset_value();
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
    reset_value();
    return SUCCESS;
}

static
int send_attack(player_t *player, char case_letter, char case_number)
{
    int ping_letter = case_letter - 'A';
    int ping_number = case_number - '1';
    int count = 0;

    for (int i = 0; i < ping_letter; i += 1) {
        usleep(1000);
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
    for (int i = 0; i != Y_CASE; i += 1)
        for (int j = 0; j != X_CASE; j += 1)
            if (player->map[i][j] != '.' && player->map[i][j] != 'o' && player->map[i][j] == 'x')
                count = 1;
    if (count == 0)
        if (kill(player->enemy_pid, player->signal_stop) == -1) {
            return display_error("Unable to send win");
        }
    player->my_turn = FALSE;
    return SUCCESS;
}

static
void display_attack(char *buff)
{
    my_putchar(buff[0]);
    my_putchar(buff[1]);
    my_putstr(": ");
}

int play_turn(player_t *player)
{
    char buff[3] = "zz";

    if (player == NULL)
        return FAILURE;
    while (TRUE) {
        my_putstr("attack: ");
        if (read(STDIN_FILENO, buff, 3) == -1)
            return display_error("Unable to read the attack\n");
        if ((buff[0] < 'A' || buff[0] > 'H') ||
            (buff[1] < '1' || buff[1] > '8') || buff[2] != '\n') {
            my_putstr("Wrong position\n");
            continue;
        }
        break;
    }
    if (send_attack(player, buff[0], buff[1]) == FAILURE)
        return FAILURE;
    display_attack(buff);
    return get_hit_enemy(player, buff[0] - 'A', buff[1] - '1');
}
