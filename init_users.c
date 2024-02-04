/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** init_users
*/

#include "include/my.h"
#include "include/my_navy.h"

extern int global_int;

static void handle_usr2(int signal, siginfo_t *info, void *context)
{
    my_putstr("\n\nenemy connected\n\n");
    global_int = info->si_pid;
}

static void handle_usr1(int signal, siginfo_t *info, void *context)
{
    my_putstr("\n\nsuccessfully connected\n\n");
    global_int = info->si_pid;
}

void init_player1(my_board_t *board)
{
    struct sigaction sa;
    struct sigaction old;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_usr2;
    sigaction(SIGUSR1, &sa, &old);
    pause();
    board->enemy_pid = global_int;
    sigaction(SIGUSR1, &old, NULL);
}

void init_player2(void)
{
    struct sigaction sa;
    struct sigaction old;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_usr1;
    sigaction(SIGUSR1, &sa, &old);
    pause();
    sigaction(SIGUSR1, &old, NULL);
}
