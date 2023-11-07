#include "../inc/pathfinder.h"

void usage_error(int argc) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(1);
    }
}
