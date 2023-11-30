#include "uls.h"

char **mx_take_xtr_info(const char *filename) {
    char buffer[1024] = {'\0'};
    ssize_t counter = listxattr(filename, buffer, sizeof(buffer), XATTR_NOFOLLOW);

    for (int i = 0; i < counter - 1; i++) {
        if (buffer[i] == '\0') {
            buffer[i] = ':';
        }
    }

    if (counter > 0) {
        return mx_strsplit(buffer, ':');
    }

    return NULL;
}
