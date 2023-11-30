#include "uls.h"

char *mx_change_unprintable(const char *name) {
    char *cpy = mx_strdup(name);

    for (int i = 0; cpy[i] != '\0'; i++) {
        if (cpy[i] >= 0
            && cpy[i] <= 31) {
            cpy[i] = '?';
        }
    }

    return cpy;
}
