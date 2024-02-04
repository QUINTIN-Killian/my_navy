/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** link_process
*/
#include "include/my_navy.h"
#include "include/my.h"

extern int global_int;

void link_process_usr1(my_board_t *board)
{
    my_putstr("my_pid: ");
    my_put_nbr(init_infos(board, (pid_t)-1));
    my_putstr("\n\nwaiting for enemy connection...");
    init_player1(board);
    global_int = 1;
    kill(board->enemy_pid, SIGUSR1);
}

void link_process_usr2(my_board_t *board, char **av)
{
    my_putstr("my_pid: ");
    my_put_nbr(init_infos(board, (pid_t)convert_str_in_int(av[1])));
    kill(board->enemy_pid, SIGUSR1);
    init_player2();
    global_int = 1;
}
