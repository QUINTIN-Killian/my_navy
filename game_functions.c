/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** some game functions
** game_functions
*/

#include "include/my.h"
#include "include/my_navy.h"

extern int global_int;

void print_pattern(void)
{
    my_putstr("\nresult: ");
    my_putchar(global_int / 100);
    my_putchar(global_int % 100);
    my_putstr(":");
}

void is_hit(my_board_t *board)
{
    if (board->my_positions[(global_int % 100) - '1']
    [(global_int / 100 - 'A') * 2] >= '1' &&
    board->my_positions[(global_int % 100) - '1']
    [(global_int / 100 - 'A') * 2] <= '9') {
        board->my_positions[(global_int % 100) - '1']
        [(global_int / 100 - 'A') * 2] = 'x';
        print_pattern();
        my_putstr("hit\n\n");
        kill(board->enemy_pid, SIGUSR1);
    } else {
        if (board->my_positions[(global_int % 100) - '1']
        [(global_int / 100 - 'A') * 2] == '.')
            board->my_positions[(global_int % 100) - '1']
            [(global_int / 100 - 'A') * 2] = 'o';
        print_pattern();
        my_putstr("missed\n\n");
        kill(board->enemy_pid, SIGUSR2);
    }
}

static void sighandler_hit(int signal, siginfo_t *info, void *context)
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &sighandler_sigusr2;
    print_pattern();
    my_putstr("hit\n\n");
    global_int *= 10;
    global_int += 1;
    sigaction(SIGUSR1, context, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}

static void sighandler_missed(int signal, siginfo_t *info, void *context)
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = &sighandler_sigusr1;
    print_pattern();
    my_putstr("missed\n\n");
    global_int *= 10;
    global_int += 2;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, context, NULL);
}

void get_hit(void)
{
    struct sigaction sa1;
    struct sigaction sa2;
    struct sigaction old1;
    struct sigaction old2;

    sa1.sa_flags = SA_SIGINFO;
    sa1.sa_sigaction = &sighandler_hit;
    sigaction(SIGUSR1, &sa1, &old1);
    sa2.sa_flags = SA_SIGINFO;
    sa2.sa_sigaction = &sighandler_missed;
    sigaction(SIGUSR2, &sa2, &old2);
}

void symbol_on_map(my_board_t *board)
{
    char *tmp = convert_int_to_str(global_int);

    if (tmp[4] == '1') {
        global_int -= 1;
        global_int = global_int / 10;
        board->enemys_positions[(global_int % 100) - '1']
        [(global_int / 100 - 'A') * 2] = 'x';
    } else {
        global_int -= 2;
        global_int = global_int / 10;
        if (board->enemys_positions[(global_int % 100) - '1']
        [(global_int / 100 - 'A') * 2] == '.')
            board->enemys_positions[(global_int % 100) - '1']
            [(global_int / 100 - 'A') * 2] = 'o';
    }
    free(tmp);
}
