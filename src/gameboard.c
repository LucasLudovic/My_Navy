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
int display_player_gameboard(player_t *player)
{
    my_putstr("my positions:\n");
    my_putstr(" |A B C D E F G H\n");
    my_putstr("-+---------------\n");
    for (int i = 0; i < Y_CASE; i += 1) {
        my_putchar(i + '1');
        my_putchar('|');
        for (int j = 0; j < X_CASE; j += 1) {
            write(1, &player->map[i][j], 1);
            if (j < X_CASE - 1)
                my_putchar(' ');
        }
        my_putchar('\n');
    }
}

int display_user_gameboard(player_t *player)
{
    //supprimer ces deux lignes une fois que la map est initialisée
    player->map = my_str_to_word_array("12345678 87654321 12345678 87654321");
    player->enemy_map = my_str_to_word_array("........ ........ ........ ........ ........ ........ ........");
    if (player == NULL || player->map == NULL || player->enemy_map == NULL)
        return FAILURE;
    display_player_gameboard(player);
    return SUCCESS;
}
