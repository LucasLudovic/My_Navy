/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Main for the solo stumper
*/

#include <signal.h>
#include <unistd.h>
#include "my.h"
#include "my_macros.h"

void wait_connection(player_t *player)
{
    pid_t pid = getpid();

    my_putstr("my_pid:");
    my_putnbr(pid);
    my_putstr("\nwaiting for enemy connection...\n");
    return TRUE;
}