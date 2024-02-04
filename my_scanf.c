/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** get the user input in the terminal
** my_scanf
*/

#include "include/my.h"
#include "include/my_navy.h"

char *my_scanf(void)
{
    char *lineptr = NULL;
    char *ans = NULL;
    size_t n = 0;

    getline(&lineptr, &n, stdin);
    ans = my_strndup(lineptr, my_strlen(lineptr) - 1);
    free(lineptr);
    return ans;
}

bool is_target_correct(char *target)
{
    if (target == NULL || my_strlen(target) != 2)
        return False;
    if (target[0] < 'A' || (target[0] > 'H' && target[0] < 'a') ||
    target[0] > 'z')
        return False;
    if (target[1] < '1' || target[1] > '8')
        return False;
    return True;
}

void send_pos(my_board_t *board, char *pos)
{
    for (int i = 0; i <= pos[0] - 'A'; i++)
        kill(board->enemy_pid, SIGUSR1);
    for (int i = 0; i <= pos[1] - '1'; i++)
        kill(board->enemy_pid, SIGUSR2);
    kill(board->enemy_pid, SIGUSR1);
}
