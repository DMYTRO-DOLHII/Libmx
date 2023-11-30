#include "uls.h"

t_flags *mx_make_flags(void) {
    t_flags *flags = malloc(sizeof(t_flags));
    mx_memset(flags, 0, sizeof(t_flags));

    if (isatty(1)) {
        flags->format = DEFAULT_OUTPUT;
    }

    return flags;
}
