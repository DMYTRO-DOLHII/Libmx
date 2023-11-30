#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (str == NULL
        || sub == NULL
        || replace == NULL) {
        return NULL;
    }

    int length_diff = mx_strlen(replace) - mx_strlen(sub);
    int new_length = mx_strlen(str) + mx_count_substr(str, sub) * length_diff;
    char *new_str = mx_strnew(new_length);

    for (int i = 0; i < new_length; i++, str++) {
        if (mx_strncmp((char *)str, (char *)sub, mx_strlen(sub)) == 0) {
            str += mx_strlen(sub);

            for (int j = 0; j < mx_strlen(replace); i++, j++) {
                new_str[i] = replace[j];
            }
        }

        new_str[i] = *str;
    }

    return new_str;
}

