#include "../inc/pathfinder.h"

static int size_strarr(char **strarr) {
    int size = 0;
    for (int i = 0; strarr[i]; i++) {
        size++;
    }
    return size;
}

void invalid_islands(const char *filename) {;
    char *str = mx_file_to_str(filename);
    char **strarr = mx_strsplit(str, '\n');
    char **check_arr = vertex(str, (size_strarr(strarr) * 2));

    if (size_strarr(check_arr) != mx_atoi(strarr[0])) {
        mx_printerr("error: invalid number of islands\n");
        exit(1);
    }

    mx_strdel(&str);
    mx_del_strarr(&strarr);
    mx_del_strarr(&check_arr);
}