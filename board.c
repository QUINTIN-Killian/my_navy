/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** board functions
** board
*/

#include "include/my.h"
#include "include/my_navy.h"

void destroy_board(char **board)
{
    for (int i = 0; i < 8; i++)
        free(board[i]);
    free(board);
}

char **create_board(void)
{
    char **board = malloc(sizeof(char *) * 9);

    for (int i = 0; i < 8; i++)
        board[i] = my_strdup(". . . . . . . .\n");
    board[8] = NULL;
    return board;
}

static void print_board(char **board, char *print_player)
{
    my_putstr(print_player);
    my_putstr(" |A B C D E F G H\n");
    my_putstr("-+---------------\n");
    my_putstr("1|");
    my_putstr(board[0]);
    my_putstr("2|");
    my_putstr(board[1]);
    my_putstr("3|");
    my_putstr(board[2]);
    my_putstr("4|");
    my_putstr(board[3]);
    my_putstr("5|");
    my_putstr(board[4]);
    my_putstr("6|");
    my_putstr(board[5]);
    my_putstr("7|");
    my_putstr(board[6]);
    my_putstr("8|");
    my_putstr(board[7]);
}

void print_boards(my_board_t *board)
{
    print_board(board->my_positions, "my navy:\n");
    my_putchar('\n');
    print_board(board->enemys_positions, "enemy navy:\n");
    my_putchar('\n');
}

static int max(int a, int b)
{
    if (a < b)
        return b;
    return a;
}

static int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

void init_my_board(char **my_board, char **word_array)
{
    int x_max;
    int y_max;
    int x_min;
    int y_min;

    for (int i = 0; i <= 9; i += 3) {
        x_max = max(word_array[i + 1][0] - 'A', word_array[i + 2][0] - 'A');
        y_max = max(word_array[i + 1][1] - '1', word_array[i + 2][1] - '1');
        x_min = min(word_array[i + 1][0] - 'A', word_array[i + 2][0] - 'A');
        y_min = min(word_array[i + 1][1] - '1', word_array[i + 2][1] - '1');
        for (int j = x_min; j <= x_max; j++)
            my_board[y_min][j * 2] = word_array[i][0];
        for (int j = y_min; j <= y_max; j++)
            my_board[j][x_min * 2] = word_array[i][0];
    }
}

bool shoot_at_pos(my_board_t *board, char *pos)
{
    bool ans = False;
    int x = pos[0] - 'A';
    int y = pos[1] - '1';

    if (board->enemys_positions[y][x * 2] != '.' &&
    board->enemys_positions[y][x * 2] != 'x')
        ans = True;
    board->enemys_positions[y][x * 2] = 'x';
    return ans;
}
