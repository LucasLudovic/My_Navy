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
int get_signal(int increment, int signal)
{
    static int last_signal = 0;

    if (increment == ADD)
        last_signal = signal;
    return last_signal;
}

static
void handle_signal(int signal)
{
    get_signal(ADD, signal);
}

int wait_connection(void)
{
    struct sigaction sig_action;
    int received_signal = NO_SIGNAL;

    sig_action.sa_flags = 0;
    sig_action.sa_handler = handle_signal;
    sigemptyset(&sig_action.sa_mask);

    if (sigaction(SIGUSR2, &sig_action, NULL) == -1)
        return display_error("Invalid use of sigaction\n");
    while (received_signal != SIGUSR2)
    {
        pause();
        received_signal = get_signal(GET, 0);
    }
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
    sig_action.sa_handler = handle_signal;
    sigemptyset(&sig_action.sa_mask);
    if (sigaction(SIGUSR1, &sig_action, NULL) == -1)
        return display_error("Invalid use of sigaction\n");
    if (kill(pid_to_ping, SIGUSR2) == -1)
        return display_error("Wrong value of PID entered\n");
    while (received_signal != SIGUSR1)
    {
        pause();
        received_signal = get_signal(GET, 0);
    }
    return SUCCESS;
}
