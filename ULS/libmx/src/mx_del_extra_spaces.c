#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *temp_str = mx_strtrim(str);

    if (str == NULL
        || temp_str == NULL) {
        return NULL;
    }

    int space_count = 0;

    for (int i = 0; i < mx_strlen(temp_str) - 1; i++) {
        if (mx_isspace(temp_str[i])
            && mx_isspace(temp_str[i + 1])) {
            space_count++;
        }
    }

    char *new_str = mx_strnew(mx_strlen(temp_str) - space_count);

    for (int i = 0, j = 0; i < mx_strlen(temp_str); i++, j++) {
        if (!mx_isspace(temp_str[i])) {
            new_str[j] = temp_str[i];
        }

        if (mx_isspace(temp_str[i])
            && !mx_isspace(temp_str[i + 1])) {
            new_str[j] = ' ';
        }
    }

    mx_strdel(&temp_str);

    return new_str;
}

