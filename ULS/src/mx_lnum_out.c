#include "uls.h"

void mx_lnum_out(long long number, int width) {
    char *string = mx_lltoa(number);
    mx_print_l_str(string, width, true);
    free(string);
}
