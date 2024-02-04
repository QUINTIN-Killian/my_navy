/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** header for the my_navy project
** my_navy
*/

#ifndef MY_NAVY_H_
    #define MY_NAVY_H_
    #define BUFF_SIZE 32
    #define _POSIX_C_SOURCE 200809L
    #define _GNU_SOURCE
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <sys/signal.h>

typedef enum boolean {
    False,
    True
} bool;

typedef struct my_board_s {
    pid_t my_pid;
    pid_t enemy_pid;
    char **my_positions;
    char **enemys_positions;
} my_board_t;

//file.c :
char **get_buffer_file(char *filepath);

//board.c :
void destroy_board(char **board);
char **create_board(void);
void print_boards(my_board_t *board);
void init_my_board(char **my_board, char **word_array);

//game_functions.c :
void print_pattern(void);
void is_hit(my_board_t *board);
void get_hit(void);
void symbol_on_map(my_board_t *board);

//end.c :
bool is_game_finished_for_me(char **board);
bool is_game_finished_for_enemy(char **board);
int end_game(my_board_t *board);

//game.c :
void my_sleep(int seconds);
pid_t init_infos(my_board_t *board, pid_t enemy_pid);
int game_loop(int ac, char **av, my_board_t *board);
void sighandler_sigusr1(int signal, siginfo_t *info,
    void *context);
void sighandler_sigusr2(int signal, siginfo_t *info,
    void *context);

//link_process.c :
void link_process_usr1(my_board_t *board);
void link_process_usr2(my_board_t *board, char **av);

//my_scanf.c :
char *my_scanf(void);
bool is_target_correct(char *target);

//init_users.c :
void init_player1(my_board_t *board);
void init_player2(void);

//turn_handling.c :
int turn_usr1(my_board_t *board);
int turn_usr2(my_board_t *board);

//signals.c :
void get_signal(void);
void send_target_pos(my_board_t *board, char *pos);

#endif
