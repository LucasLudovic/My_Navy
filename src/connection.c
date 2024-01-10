/*
** EPITECH PROJECT, 2024
** Connection
** File description:
** Handle the connection for the navy
*/

#include <signal.h>
#include <unistd.h>
#include "player.h"
#include "my.h"
#include "my_macros.h"

void display_pid(player_t *player)
{
    pid_t pid = getpid();

    my_putstr("my_pid: ");
    my_put_nbr(pid);
    my_putchar('\n');
    if (player->id == 1)
        my_putstr("waiting for enemy connection...\n");
}

static
int get_info(int increment, siginfo_t *info, int signal)
{
    static int last_signal = NO_SIGNAL;
    static pid_t last_pid_other = 0;

    if (increment == GET_SIGNAL)
        return last_signal;
    if (increment == GET_PID)
        return (int)last_pid_other;
    if (increment == ADD) {
        last_signal = signal;
        if (info == NULL)
            return FAILURE;
        last_pid_other = info->si_pid;
    }
    return last_signal;
}

static
void handle_signal(int signal, siginfo_t *info, void *context)
{
    get_info(ADD, info, signal);
}

int wait_connection(player_t *player)
{
    struct sigaction sig_action;
    int received_signal = NO_SIGNAL;

    if (player == NULL)
        return display_error("Wrong player entered\n");
    sig_action.sa_flags = SA_SIGINFO;
    sig_action.sa_sigaction = handle_signal;
    sigemptyset(&sig_action.sa_mask);
    if (sigaction(SIGUSR2, &sig_action, NULL) == -1)
        return display_error("Invalid use of sigaction\n");
    while (received_signal != SIGUSR2) {
        pause();
        received_signal = get_info(GET_SIGNAL, NULL, NO_SIGNAL);
    }
    player->enemy_pid = get_info(GET_PID, NULL, NO_SIGNAL);
    if (kill(player->enemy_pid, player->signal_send) == -1)
        return FAILURE;
    my_putstr("enemy connected\n");
    return SUCCESS;
}

int request_connection(char const *pid_str)
{
    struct sigaction sig_action;
    int received_signal = NO_SIGNAL;
    int pid_to_ping = 0;

    if (pid_str == NULL || my_str_isnum(pid_str) == FALSE)
        return display_error("Wrong value of pid\n");
    pid_to_ping = my_getnbr(pid_str);
    if (pid_to_ping < 0)
        return display_error("A pid must always be positive\n");
    sig_action.sa_flags = 0;
    sig_action.sa_sigaction = handle_signal;
    sigemptyset(&sig_action.sa_mask);
    if (sigaction(SIGUSR1, &sig_action, NULL) == -1)
        return display_error("Invalid use of sigaction\n");
    if (kill(pid_to_ping, SIGUSR2) == -1)
        return display_error("Wrong value of PID entered\n");
    while (received_signal != SIGUSR1) {
        pause();
        received_signal = get_info(GET_SIGNAL, NULL, NO_SIGNAL);
    }
    my_putstr("successfully connected\n");
    return SUCCESS;
}
