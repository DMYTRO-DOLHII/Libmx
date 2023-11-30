#include "uls.h"

void mx_element_size_output(off_t size, int width) {
    const char *all_s[] = {"B", "K", "M", "G", "T", "P"};
    double f_size = size;
    int suf = 0;

    while (f_size >= 1000) {
        f_size /= 1024;
        suf++;
    }

    double size_r = mx_long_round(f_size * 10) / 10;
    char buf[5] = {'\0'};

    if (size_r >= 10
        || suf == 0) {
        char *str = mx_lltoa(mx_long_round(f_size));
        mx_strcat(buf, str);
        free(str);
    } else {
        char *str = mx_lltoa(size_r);
        mx_strcat(buf, str);
        free(str);
        mx_strcat(buf, ".");
        str = mx_lltoa((long long)(size_r * 10) % 10);
        mx_strcat(buf, str);
        free(str);
    }

    mx_strcat(buf, all_s[suf]);
    mx_print_l_str(buf, width, true);
}
