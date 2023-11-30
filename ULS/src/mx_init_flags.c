#include "uls.h"

t_flags *mx_init_flags(int argc, char *argv[]) {
    t_flags *flags = mx_make_flags();

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            break;
        }

        for (char *str = argv[i] + 1; *str != '\0'; str++) {
            if (*str == 'R') {
                flags->is_R = true;
            } else if (*str == 'G') {
                flags->is_G = true;
            } else if (*str == 'F') {
                flags->is_F = true;
                flags->is_p = false;
            } else if (*str == 'p') {
                flags->is_p = true;
                flags->is_F = false;
            } else if (*str == 'r') {
                flags->is_rev = true;
            } else if (*str == 'h') {
                flags->is_h = true;
            } else if (*str == 'e') {
                flags->is_e = true;
            } else if (*str == 'T') {
                flags->is_T = true;
            } else if (*str == '@') {
                flags->is_at = true;
            } else if (*str == 'g') {
                flags->is_g = true;
            } else if (*str == 'o') {
                flags->is_o = true;
            } else if (*str == 'x') {
                flags->is_x = true;
            } else if (*str == 'n') {
                flags->is_n = true;
            } else if (*str == 'q') {
                flags->is_q = true;
            } else if (*str == 'H') {
                flags->is_H = true;
            } else if (*str == '1') {
                flags->format = ONECOL_OUTPUT;
            } else if (*str == 'C') {
                flags->format = DEFAULT_OUTPUT;
            } else if (*str == 'm') {
                flags->format = ONEROW_OUTPUT;
            } else if (*str == 'l') {
                flags->format = L_OUTPUT;
            } else if (*str == 'c') {
                flags->time_type = STAT;
            } else if (*str == 'u') {
                flags->time_type = ACC;
            } else if (*str == 'U') {
                flags->time_type = CREATE;
            } else if (*str == 't') {
                flags->sort_type = TIME;
            } else if (*str == 'S') {
                flags->sort_type = SIZE;
            } else if (*str == 'f') {
                flags->sort_type = NONE;
                flags->ommit = ZERO;
            } else if (*str == 'A') {
                flags->ommit = DOTS;
            } else if (*str == 'a') {
                flags->ommit = ZERO;
            } else {
                mx_printerr("uls: illegal option -- ");
                write(2, str, 1);
                write(2, "\n", 1);
                mx_printerr("usage: uls [-@ACFGHRSTUacefghlmnopqrtux1] [file ...]\n");
                exit(1);
            }

        }
    }

    if (!isatty(1)) {
        flags->is_G = false;
    } else {
        flags->is_q = true;
    }

    if (!flags->is_H) {
        flags->is_H =
                flags->format != L_OUTPUT
                && !flags->is_G
                && !flags->is_F;
    }

    if (flags->sort_type == NONE) {
        flags->ommit = ZERO;
    }

    return flags;
}
