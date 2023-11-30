#include "uls.h"

    int mx_element_class_output(mode_t mode, bool is_p_only) {
        char character = '\0';
    if ((mode & S_IFMT) == S_IFDIR) {
        character = '/';
    } else if ((mode & S_IFMT) == S_IFIFO) {
        character = '|';
    } else if ((mode & S_IFMT) == S_IFLNK) {
        character = '@';
    } else if ((mode & S_IFMT) == S_IFSOCK) {
        character = '=';
    } else if ((mode & S_IFMT) == S_IFREG) {
        if (mode & (S_IXUSR | S_IXGRP | S_IXOTH)) {
            character = '*';
        }
    }

    if (character != '\0') {
        if (is_p_only && character != '/') {
            return 0;
        }

        mx_printchar(character);

        return 1;
    }

    return 0;
}
