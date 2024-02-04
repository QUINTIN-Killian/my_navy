/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** manage signals
** signals
*/

#include "include/my.h"
#include "include/my_navy.h"

extern int global_int;

static void sighandler_plus_one(int signal, siginfo_t *info, void *context)
{
    global_int += 1;
}

static void sighandler_switch(int signal, siginfo_t *info, void *context)
{
    struct sigaction sa1;
    struct sigaction sa2;

    if (my_intlen(global_int) == 2) {
        global_int *= 100;
        global_int += '1' - 1;
    } else if (my_intlen(global_int) == 4) {
        sa1.sa_flags = SA_SIGINFO;
        sa2.sa_flags = SA_SIGINFO;
        sa1.sa_sigaction = &sighandler_sigusr1;
        sa2.sa_sigaction = &sighandler_sigusr2;
        sigaction(SIGUSR1, &sa1, NULL);
        sigaction(SIGUSR2, &sa2, NULL);
    }
}

void get_signal(void)
{
    struct sigaction sa2;
    struct sigaction sa1;
    struct sigaction old2;
    struct sigaction old1;

    global_int = 'A' - 1;
    sa2.sa_flags = SA_SIGINFO;
    sa2.sa_sigaction = &sighandler_plus_one;
    sigaction(SIGUSR2, &sa2, &old2);
    sa1.sa_flags = SA_SIGINFO;
    sa1.sa_sigaction = &sighandler_switch;
    sigaction(SIGUSR1, &sa1, &old1);
}

void send_target_pos(my_board_t *board, char *pos)
{
    for (int i = 'A' - 1; i < pos[0]; i++) {
        kill(board->enemy_pid, SIGUSR2);
        usleep(1000);
    }
    kill(board->enemy_pid, SIGUSR1);
    usleep(1000);
    for (int i = '1' - 1; i < pos[1]; i++) {
        kill(board->enemy_pid, SIGUSR2);
        usleep(1000);
    }
}
