/*
** EPITECH PROJECT, 2024
** my_navy
** File description:
** check the file content
** file
*/

#include "include/my.h"
#include "include/my_navy.h"

static int check_correct_nbr_of_boats_aux(char **word_array, int i)
{
    for (int j = i + 3; j <= 9; j += 3)
        if (word_array[i][0] == word_array[j][0])
            return 84;
    return 0;
}

static int check_correct_nbr_of_boats(char **word_array)
{
    for (int i = 0; i != 9; i += 3)
        if (check_correct_nbr_of_boats_aux(word_array, i) == 84)
            return 84;
    return 0;
}

static char **check_buffer_content_aux(int i, char **word_array)
{
    if (word_array[i + 1][1] < '1' || word_array[i + 1][1] > '8' ||
    word_array[i + 2][1] < '1' || word_array[i + 2][1] > '8')
        return NULL;
    if (my_abs((word_array[i + 1][0] - 48) - (word_array[i + 2][0] - 48)) !=
    (word_array[i][0] - 48) - 1 && my_abs((word_array[i + 1][0] - 48) -
    (word_array[i + 2][0] - 48)) != 0)
        return NULL;
    if (my_abs((word_array[i + 1][1] - 48) - (word_array[i + 2][1] - 48)) !=
    (word_array[i][0] - 48) - 1 && my_abs((word_array[i + 1][1] - 48) -
    (word_array[i + 2][1] - 48)) != 0)
        return NULL;
    if (my_abs((word_array[i + 1][0] - 48) - (word_array[i + 2][0] - 48)) ==
    (word_array[i][0] - 48) - 1 && my_abs((word_array[i + 1][1] - 48) -
    (word_array[i + 2][1] - 48)) != 0)
        return NULL;
    if (my_abs((word_array[i + 1][1] - 48) - (word_array[i + 2][1] - 48)) ==
    (word_array[i][0] - 48) - 1 && my_abs((word_array[i + 1][0] - 48) -
    (word_array[i + 2][0] - 48)) != 0)
        return NULL;
    return word_array;
}

char **check_buffer_content(char *buff)
{
    char **word_array = my_str_to_word_array(buff);

    if (buff[1] != ':' || buff[4] != ':' || buff[9] != ':' || buff[12] != ':'
    || buff[17] != ':' || buff[20] != ':' || buff[25] != ':' ||
    buff[28] != ':' || check_correct_nbr_of_boats(word_array) == 84)
        return NULL;
    for (int i = 0; i < my_strlen_array(word_array); i += 3) {
        if (my_strlen(word_array[i]) != 1 || my_strlen(word_array[i + 1]) != 2
        || my_strlen(word_array[i + 2]) != 2)
            return NULL;
        if (word_array[i][0] - 48 < 2 || word_array[i][0] - 48 > 5)
            return NULL;
        if (word_array[i + 1][0] < 'A' || word_array[i + 1][0] > 'H' ||
        word_array[i + 2][0] < 'A' || word_array[i + 2][0] > 'H')
            return NULL;
        if (check_buffer_content_aux(i, word_array) == NULL)
            return NULL;
    }
    return word_array;
}

static int read_file(int fd, int *total)
{
    int len;
    char buff[1];

    len = read(fd, buff, 1);
    while (len > 0) {
        *total += 1;
        if (*total > BUFF_SIZE) {
            close(fd);
            return 84;
        }
        len = read(fd, buff, 1);
    }
    close(fd);
    return 0;
}

int check_file_len(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    int total = 0;

    if (fd == -1) {
        close(fd);
        return 84;
    }
    if (read_file(fd, &total) == 84)
        return 84;
    if (total != BUFF_SIZE)
        return 84;
    return 0;
}

char **get_buffer_file(char *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char buff[BUFF_SIZE + 1];
    int len;

    if (fd == -1 || check_file_len(filepath) == 84) {
        close(fd);
        return NULL;
    }
    len = read(fd, buff, BUFF_SIZE);
    close(fd);
    if (len < BUFF_SIZE)
        return NULL;
    buff[BUFF_SIZE] = '\0';
    return check_buffer_content(buff);
}
