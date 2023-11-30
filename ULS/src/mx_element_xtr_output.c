#include "uls.h"

void mx_element_xtr_output(t_element *elements_data, bool is_h) {
    for (char **ptr = elements_data->xattr_keys; *ptr != NULL; ptr++) {
        mx_printchar('\t');
        mx_printstr(*ptr);
        mx_printchar('\t');
        ssize_t value_size = getxattr(elements_data->path, *ptr, NULL, 0, 0, XATTR_NOFOLLOW);

        if (is_h) {
            mx_element_size_output(value_size, 5);
        } else {
            mx_lnum_out(value_size, 4);
        }

        mx_printstr(" \n");
    }
}
