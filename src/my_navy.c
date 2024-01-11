/*
** EPITECH PROJECT, 2024
** navy
** File description:
** my_navy.c
*/

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "my_macros.h"
#include "connection.h"
#include "gameboard.h"

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

int my_navy(int argc, char **argv)
{
    player_t *player = NULL;
    int game_on = TRUE;

    player = malloc(sizeof(player_t));
    if (player == NULL)
        return destroy_end(player);
    player->id = argc - 1;
    display_pid(player);
    if (connect_player(player, argc, argv) == FAILURE)
        return destroy_end(player);
    while (game_on) {
        if (display_user_gameboard(player) == FAILURE)
            return destroy_end(player);
        sleep(1);
    }
    destroy_end(player);
    return SUCCESS;
}
