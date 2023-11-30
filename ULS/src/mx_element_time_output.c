#include "uls.h"

void mx_element_time_output(time_t ptime, bool full) {
    char *str = ctime(&ptime);
    char **arr = mx_strsplit(str, ' ');
    time_t current = time(NULL);
    time_t sec_6_mon = (365 / 2) * 24 * 60 * 60;
    arr[4][4] = '\0';

    if (full) {
        for (int i = 1; arr[i] != NULL; i++) {
            mx_print_l_str(arr[i], 2, true);

            if (arr[i + 1] != NULL) {
                mx_printchar(' ');
            }
        }
    } else if (ptime + sec_6_mon <= current
               || ptime >= current + sec_6_mon) {
        mx_printstr(arr[1]);
        mx_printchar(' ');
        mx_print_l_str(arr[2], 2, true);
        mx_printstr("  ");
        mx_printstr(arr[4]);
    } else {
        mx_printstr(arr[1]);
        mx_printchar(' ');
        mx_print_l_str(arr[2], 2, true);
        mx_printchar(' ');
        char **arr_time = mx_strsplit(arr[3], ':');
        mx_printstr(arr_time[0]);
        mx_printchar(':');
        mx_printstr(arr_time[1]);
        mx_del_strarr(&arr_time);
    }

    mx_del_strarr(&arr);
}
