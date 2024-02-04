/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** turn_handling
*/

#include "include/my.h"
#include "include/my_navy.h"

extern int global_int;

static void send_out_of_pause(my_board_t *board, char *target)
{
    for (int i = 0; i < 'H' - target[0]; i++) {
        kill(board->enemy_pid, SIGUSR1);
        usleep(1000);
    }
    for (int i = 0; i < '8' - target[1]; i++) {
        kill(board->enemy_pid, SIGUSR1);
        usleep(1000);
    }
}

void turn(my_board_t *board)
{
    char *target;

    my_putstr("attack: ");
    target = my_scanf();
    while (!is_target_correct(target)) {
        free(target);
        my_putstr("\nwrong position\n");
        my_putstr("\nattack: ");
        target = my_scanf();
    }
    target = my_strupcase(target);
    send_target_pos(board, target);
    kill(board->enemy_pid, SIGUSR1);
    usleep(1000);
    send_out_of_pause(board, target);
    global_int = target[0];
    global_int *= 100;
    global_int += target[1];
}

static void set_pause(int n)
{
    if (n > 0) {
        pause();
        set_pause(n - 1);
    }
}

static void enemys_turn(my_board_t *board)
{
    my_putstr("waiting for enemy's attack...");
    get_signal();
    set_pause(18);
    usleep(1500);
    my_putchar('\n');
    is_hit(board);
}

static void my_turn(my_board_t *board)
{
    turn(board);
    get_hit();
    pause();
    symbol_on_map(board);
}

int turn_usr1(my_board_t *board)
{
    while (!is_game_finished_for_me(board->my_positions) &&
    !is_game_finished_for_enemy(board->enemys_positions)) {
        if (global_int == 0) {
            enemys_turn(board);
            global_int = 1;
        } else {
            print_boards(board);
            my_turn(board);
            global_int = 0;
        }
    }
    print_boards(board);
    return end_game(board);
}

int turn_usr2(my_board_t *board)
{
    while (!is_game_finished_for_me(board->my_positions) &&
    !is_game_finished_for_enemy(board->enemys_positions)) {
        if (global_int == 1) {
            print_boards(board);
            enemys_turn(board);
            global_int = 0;
        } else {
            my_turn(board);
            global_int = 1;
        }
    }
    print_boards(board);
    return end_game(board);
}
