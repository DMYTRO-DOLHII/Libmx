#include "uls.h"

void mx_element_acl_ouyput(acl_t acl) {
    char *str = acl_to_text(acl, NULL);
    char **rows = mx_strsplit(str, '\n');

    for (int i = 1; rows[i] != NULL; i++) {
        mx_printchar(' ');
        mx_printint(i - 1);
        mx_printstr(": ");
        char **parts = mx_strsplit(rows[i], ':');
        mx_printstr(parts[0]);
        mx_printchar(':');
        mx_printstr(parts[2]);
        mx_printchar(' ');
        mx_printstr(parts[4]);
        mx_printchar(' ');
        mx_printstr(parts[5]);
        mx_printchar('\n');
        mx_del_strarr(&parts);
    }

    mx_del_strarr(&rows);
    free(str);
}
