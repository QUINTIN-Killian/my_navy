/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** game actions
** game
*/

#include "include/my.h"
#include "include/my_navy.h"

extern int global_int;

void my_sleep(int seconds)
{
    for (int i = 0; i < seconds * 2; i++)
        usleep(500000);
}

pid_t init_infos(my_board_t *board, pid_t enemy_pid)
{
    pid_t pid = getpid();

    board->my_pid = pid;
    if (enemy_pid != -1)
        board->enemy_pid = enemy_pid;
    return pid;
}

void sighandler_sigusr1(int signal, siginfo_t *info,
    void *context)
{
    return;
}

void sighandler_sigusr2(int signal, siginfo_t *info,
    void *context)
{
    return;
}

static void init_game_loop(struct sigaction *sa_usr1,
    struct sigaction *sa_usr2)
{
    sa_usr1->sa_flags = SA_SIGINFO;
    sa_usr1->sa_sigaction = &sighandler_sigusr1;
    sigaction(SIGUSR1, sa_usr1, NULL);
    sa_usr2->sa_flags = SA_SIGINFO;
    sa_usr2->sa_sigaction = &sighandler_sigusr2;
    sigaction(SIGUSR2, sa_usr2, NULL);
}

int game_loop(int ac, char **av, my_board_t *board)
{
    struct sigaction sa_usr1;
    struct sigaction sa_usr2;

    init_game_loop(&sa_usr1, &sa_usr2);
    if (ac == 2) {
        link_process_usr1(board);
        return turn_usr1(board);
    } else {
        link_process_usr2(board, av);
        return turn_usr2(board);
    }
    return -1;
}
