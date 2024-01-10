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

    my_putstr("my_pid:");
    my_put_nbr(pid);
    if (player->id == 1)
        my_putstr("\nwaiting for enemy connection...\n");
}

void wait_connection(player_t *player)
{
    pid_t pid = getpid();
    int received_signal = 0;

    while (received_signal != SIGUSR2)
        received_signal = pause();
}

void request_connection(char *pid_str)
{

}