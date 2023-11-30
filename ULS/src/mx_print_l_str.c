#include "uls.h"

void mx_print_l_str(char *string, int width, bool align_right) {
    int len = width - mx_strlen(string);

    if (!align_right) {
        mx_printstr(string);
    }

    for (int i = 0; i < len; i++) {
        mx_printchar(' ');
    }

    if (align_right) {
        mx_printstr(string);
    }
}
