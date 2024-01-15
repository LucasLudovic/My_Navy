/*
** EPITECH PROJECT, 2024
** navy
** File description:
** my_navy.c
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "my.h"
#include "my_macros.h"
#include "connection.h"
#include "my_navy.h"
#include "gameboard.h"
#include "gameloop.h"

int destroy_end(player_t *player)
{
    if (player == NULL)
        return FAILURE;
    if (player->map != NULL) {
        for (int i = 0; player->map[i] != NULL; i += 1)
            free(player->map[i]);
        free(player->map);
    }
    if (player->enemy_map != NULL) {
        for (int i = 0; player->enemy_map[i] != NULL; i += 1)
            free(player->enemy_map[i]);
        free(player->enemy_map);
    }
    free(player);
    return FAILURE;
}

static
void init_player(player_t *player, int argc, char **argv)
{
    char **map = NULL;

    player->id = argc - 1;
    player->signal_send = SIGUSR1;
    player->signal_stop = SIGUSR2;
    player->enemy_pid = NO_PID;
    if (PLAYER1)
        player->my_turn = TRUE;
    if (PLAYER2)
        player->my_turn = FALSE;
    player->enemy_map = NULL;
    map = retrieve_info_p1(player, argv);
    transform_map(map, player);
}

int my_navy(int argc, char **argv)
{
    player_t *player = NULL;

    player = malloc(sizeof(player_t));
    if (player == NULL)
        return destroy_end(player);
    init_player(player, argc, argv);
    display_pid(player);
    if (connect_player(player, argc, argv) == FAILURE)
        return destroy_end(player);
    if (loop(player) == FAILURE)
        return destroy_end(player);
    destroy_end(player);
    return SUCCESS;
}
