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
#include "gameboard.h"
#include "gameloop.h"
#include "my_navy.h"

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
int init_player(player_t *player, char **argv, int argc)
{
    char **map = NULL;

    player->id = argc - 1;
    player->signal_send = SIGUSR1;
    player->signal_stop = SIGUSR2;
    player->enemy_pid = NO_PID;
    if (PLAYER1)
        player->my_turn = TRUE;
    if (PLAYER2) {
        if (argc == 3 && argv != NULL)
            player->enemy_pid = my_getnbr(argv[1]);
        player->my_turn = FALSE;
    }
    map = retrieve_info(player, argv);
    if (transform_map(map, player) == FAILURE)
        return FAILURE;
    player->enemy_map = my_str_to_word_array("........ ........ ........"
        " ........ ........ ........"
        " ........ ........");
    return SUCCESS;
}

int my_navy(int argc, char **argv)
{
    player_t *player = NULL;
    int return_value = FAILURE;

    if (argc < 2 || argv == NULL)
        return display_error("Wrong value of args\n");
    player = malloc(sizeof(player_t));
    if (player == NULL)
        return destroy_end(player);
    if (init_player(player, argv, argc) == FAILURE)
        return FAILURE;
    display_pid(player);
    if (PLAYER2 && my_getnbr(argv[1]) < 1000)
        return display_error("You're not authorized to use this pid\n");
    if (connect_player(player, argc, argv) == FAILURE)
        return destroy_end(player);
    return_value = loop(player);
    destroy_end(player);
    return return_value;
}
