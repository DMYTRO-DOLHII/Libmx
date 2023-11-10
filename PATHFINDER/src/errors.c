#include "../inc/pathfinder.h"


static void usage_error(int argc, char *argv[]) {
    if (argc != 2) {
        mx_printstr("usage: ");
        mx_printstr(argv[0]);
        mx_printstr(" [filename]\n");
        exit(EXIT_FAILURE);
    }
}



void errors(int argc, char *argv[]) {
	usage_error(argc, argv);
}