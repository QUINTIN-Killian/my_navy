/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** end game functions
** end
*/

#include "include/my.h"
#include "include/my_navy.h"

static bool is_game_finished_for_me_aux(char **board, int i)
{
    for (int j = 0; j < my_strlen(board[i]); j += 2)
        if (board[i][j] >= '0' && board[i][j] <= '9')
            return False;
    return True;
}

bool is_game_finished_for_me(char **board)
{
    for (int i = 0; i < my_strlen_array(board); i++)
        if (!is_game_finished_for_me_aux(board, i))
            return False;
    return True;
}

static void is_game_finished_for_enemy_aux(char **board, int i, int j, int *n)
{
    if (board[i][j] == 'x')
        *n += 1;
}

bool is_game_finished_for_enemy(char **board)
{
    int n = 0;

    for (int i = 0; i < my_strlen_array(board); i++)
        for (int j = 0; j < my_strlen(board[i]); j += 2)
            is_game_finished_for_enemy_aux(board, i, j, &n);
    if (n == 2 + 3 + 4 + 5)
        return True;
    return False;
}

int end_game(my_board_t *board)
{
    if (is_game_finished_for_me(board->my_positions)) {
        my_putstr("Enemy won");
        return 1;
    } else if (is_game_finished_for_enemy(board->enemys_positions)) {
        my_putstr("I won");
        return 0;
    }
    return -1;
}
