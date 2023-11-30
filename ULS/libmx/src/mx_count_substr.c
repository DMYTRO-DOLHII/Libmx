#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (str == NULL
        || sub == NULL) {
        return -1;
    }

    if (mx_strlen(sub) == 0) {
        return 0;
    }

    int i = 0;

    if (mx_strlen(str) >= mx_strlen(sub)) {
        while (*str != '\0') {
            if (!mx_strncmp((char *)str, (char *)sub, mx_strlen(sub))) {
                i++;
            }

            str++;
        }
    }

    return i;
}

