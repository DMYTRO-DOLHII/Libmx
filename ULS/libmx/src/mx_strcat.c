#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int length_s1 = mx_strlen(s1);

    for (int i = 0; i < mx_strlen(s2); i++) {
        s1[length_s1++] = s2[i];
    }

    s1[length_s1] = '\0';

    return s1;
}

