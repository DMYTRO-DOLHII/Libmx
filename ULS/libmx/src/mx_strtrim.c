#include "libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    while (mx_isspace(*str)) {
        str++;
    }

    int len = mx_strlen(str);

    if (len != 0) {
        while (mx_isspace(str[len - 1])) {
            len--;
        }
    }

    char *new_str = mx_strnew(len);
    mx_strncpy(new_str, str, len);

    return new_str;
}

