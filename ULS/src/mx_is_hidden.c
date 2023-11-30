#include "uls.h"

bool mx_is_hidden(const char *name, t_hidden ommit) {
    if (ommit == HIDDEN
        && name[0] == '.') {
        return true;
    }

    if (ommit == DOTS
        && (mx_strcmp(name, ".") == 0
        || mx_strcmp(name, "..") == 0)) {
        return true;
    }

    return false;
}
