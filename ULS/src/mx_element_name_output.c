#include "uls.h"

void mx_element_name_output(const char *name, bool is_q) {
    if (is_q) {
        char *str = mx_change_unprintable(name);
        mx_printstr(str);
        free(str);
    } else {
        mx_printstr(name);
    }
}
