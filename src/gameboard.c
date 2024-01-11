/*
** EPITECH PROJECT, 2024
** Gameboard
** File description:
** Handle the gameboard
*/

#include <stddef.h>
#include <unistd.h>
#include "my.h"
#include "my_macros.h"
#include "player.h"

static
void display_boats(char **map, int i)
{
    for (int j = 0; j < X_CASE; j += 1) {
        my_putchar(map[i][j]);
        if (j < X_CASE - 1)
            my_putchar(' ');
    }
    my_putchar('\n');
}

static
void display_single_gameboard(char display, char **map)
{
    if (display == 1)
        my_putstr("my positions:\n");
    if (display == 2)
        my_putstr("enemy's positions:\n");
    my_putstr(" |A B C D E F G H\n");
    my_putstr("-+---------------\n");
    for (int i = 0; i < Y_CASE; i += 1) {
        if (map[i] == NULL)
            break;
        my_putchar(i + '1');
        my_putchar('|');
        display_boats(map, i);
    }
}

int display_user_gameboard(player_t *player)
{
    player->map = my_str_to_word_array("12345678 87654321 12345678 87654321");
    player->enemy_map = my_str_to_word_array("........ ........ ........"
        " ........ ........ ........"
        " ........ ........");
    if (player == NULL || player->map == NULL || player->enemy_map == NULL)
        return FAILURE;
    display_single_gameboard(1, player->map);
    display_single_gameboard(2, player->enemy_map);
    return SUCCESS;
}
