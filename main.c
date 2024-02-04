/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** main file
** main
*/

#include "include/my.h"
#include "include/my_navy.h"

int global_int = 0;

static int help(void)
{
    my_putstr("USAGE\n");
    my_putstr("     ./navy [first_player_pid] navy_positions\n");
    my_putstr("DESCRIPTION\n");
    my_putstr("     first_player_pid: only for the 2nd player. ");
    my_putstr("pid of the first player.\n");
    my_putstr("     navy_positions: file representing ");
    my_putstr("the positions of the ships.\n");
    return 0;
}

char **error_handling(int ac, char **av)
{
    if (ac != 2 && ac != 3)
        return NULL;
    if (ac == 2)
        return get_buffer_file(av[1]);
    else
        return get_buffer_file(av[2]);
}

int main(int ac, char **av)
{
    char **word_array;
    my_board_t board;
    int end;

    if (ac == 2 && my_strcmp(av[1], "-h") == 0)
        return help();
    word_array = error_handling(ac, av);
    if (word_array == NULL)
        return 84;
    board.my_positions = create_board();
    board.enemys_positions = create_board();
    init_my_board(board.my_positions, word_array);
    end = game_loop(ac, av, &board);
    destroy_board(board.my_positions);
    destroy_board(board.enemys_positions);
    return end;
}
