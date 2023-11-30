#include "libmx.h"

void mx_str_reverse(char *s) {
    if (s == NULL) {
        return;
    }

    int i = 0;
    int length = mx_strlen(s) - 1;

    while (i < length) {
        mx_swap_char(&s[i], &s[length]);
        i++;
        length--;
    }
}

