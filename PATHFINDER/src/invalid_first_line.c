#include "../inc/pathfinder.h"

void invalid_first_line(const char *filename) {
    char *str = mx_file_to_str(filename);
    char **strarr = mx_strsplit(str, '\n');

    for (int i = 0; i < mx_strlen(strarr[0]); i++) {
        if (!mx_isdigit(strarr[0][i])) {
            mx_printerr("error: line 1 is not valid\n");
            exit(1);
        }
    }
    if (mx_atoi(strarr[0]) <= 0) {
        mx_printerr("error: line 1 is not valid\n");
        exit(1); 
    }

    mx_strdel(&str);
    mx_del_strarr(&strarr);
}
