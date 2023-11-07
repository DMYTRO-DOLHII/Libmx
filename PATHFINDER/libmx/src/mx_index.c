#include <libmx.h>

int mx_index(char **strarr, char *str) {
    for (int i = 0; strarr[i]; i++) {
        if (mx_strcmp(strarr[i], str) == 0) {
            return i;
        }
    }
    return -1;
}