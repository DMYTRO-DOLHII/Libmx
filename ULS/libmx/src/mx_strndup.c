#include "libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    size_t len = mx_strlen(s1);

    if (n < len) {
        len = n;
    }

    char *dup_str = NULL;
    dup_str = mx_strnew(len);

    if (!dup_str) {
        return NULL;
    }

    mx_strncpy(dup_str, s1, len);

    return dup_str;
}

