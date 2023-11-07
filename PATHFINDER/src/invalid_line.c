#include "../inc/pathfinder.h"

static void check_line(char *str, int index) {
    for (int i = 0; i < mx_strlen(str); i++) {
        if (!mx_isalpha(str[i])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(index + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
    }
}

void invalid_line(const char *filename) {
    char *str = mx_file_to_str(filename);
    char **strarr = mx_strsplit(str, '\n');

    for (int i = 1; strarr[i]; i++) {
        if (mx_get_char_index(strarr[i], '-') < 0 || mx_get_char_index(strarr[i], ',') < 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
        if (mx_count_substr(strarr[i], "-") != 1 || mx_count_substr(strarr[i], ",") != 1) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        char **str_arr = mx_strsplit(strarr[i], '-');

        check_line(str_arr[0], i);
        
        check_line(mx_strndup(str_arr[1], mx_get_char_index(str_arr[1] ,',')), i);

        for (int j = mx_get_char_index(str_arr[1] ,',') + 1; j < mx_strlen(str_arr[1]); j++) {
            if(!mx_isdigit(str_arr[1][j])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i + 1));
                mx_printerr(" is not valid\n");
                exit(1);
            }
        }

        if (mx_strcmp(str_arr[0], mx_strndup(str_arr[1], mx_get_char_index(str_arr[1] ,','))) == 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        mx_strdel(&str);
        mx_del_strarr(&str_arr);
    }
}
