#include "../inc/uls.h"

int extract_options(int argc, char *argv[], Option *options) {
    int num_argv = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int len = mx_strlen(argv[i]);
            for (int j = 1; j < len; j++) {
                if (num_argv == 0) {
                    options[num_argv++].name = argv[i][j];
                    continue;
                } 

                bool exist = false;

                for (int k = 0; k < num_argv; k++) {
                    if (options[k].name == argv[i][j]) {
                        exist = true;
                    }
                }

                if (!exist) {
                    options[num_argv++].name = argv[i][j];
                }
            }
        }
    }

    return num_argv;
}

int extract_destiations(int argc, char *argv[], Destination *destinations) {
    int num_units = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            destinations[num_units++].name = mx_strndup(argv[i] + 1, strlen(argv[i]) - 1);
        }
    }

    return num_units;
}

void enable_flags(Option *options, int size, Flag flag) {
    for (int i = 0; i < size; i++) {
        switch (options[i].name)
        {
        case 'a':
            flag.a = true;
            break;
        case 'A':
            flag.A = true;
            break;
        case 'l':
            flag.l = true;
            flag.C = false;
            flag.one = false;
            break;
        case 'r':
            flag.r = true;
            break;
        case 'R':
            flag.R = true;
            break;
        case 't':
            flag.t = true;
            break;
        case 'u':
            flag.u = true;
            break;
        case 'c':
            flag.c = true;
            break;
        case 'G':
            flag.G = true;
            break;
        case 'h':
            flag.h = true;
            break;
        case 'e':
            flag.e = true;
            break;
        case 'i':
            flag.i = true;
            break;
        case 'S':
            flag.S = true;
            break;
        case 'T':
            flag.T = true;
            break;
        case 'x':
            flag.x = true;
            break;
        case 'p':
            flag.p = true;
            break;
        case 'd':
            flag.d = true;
            break;
        case 'f':
            flag.f = true;
            break;
        case 'n':
            flag.n = true;
            break;
        case 'g':
            flag.g = true;
            break;
        case 'o':
            flag.o = true;
            break;
        case 'L':
            flag.L = true;
            break;
        case 'F':
            flag.F = true;
            break;
        case '1':
            flag.one = true;
            flag.C = false;
            flag.l = false;
            break;
        case '@':
            flag.at = true;
            break;
        case 'C':
            flag.C = true;
            flag.one = false;
            flag.l = false;
            break;
        case 'B':
            flag.B = true;
            break;
        case 's':
            flag.s = true;
            break;
        case 'X':
            flag.X = true;
            break;
        case 'v':
            flag.v = true;
            break;
        case 'w':
            flag.w = true;
            break;
        default:
            mx_printerr("Unrecognized flag: ");
            mx_printchar(options[i].name);
            mx_printstr("\n");
            exit(1);
        }
    }
}
