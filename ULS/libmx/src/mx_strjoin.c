#include "libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL
        && s2 == NULL) {
        return NULL;
    }
    else if (s1 == NULL) {
        return mx_strdup(s2);
    }
    else if (s2 == NULL) {
        return mx_strdup(s1);
    }
    else {
        char *joined_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));

        if (joined_str != NULL) {
            mx_strcpy(joined_str, s1);
            mx_strcat(joined_str, s2);
        }

        return joined_str;
    }
}

