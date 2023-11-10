#include "../inc/pathfinder.h"


static void usage_error(int argc, char *argv[]) {
    if (argc != 2) {
        mx_printstr("usage: ");
        mx_printstr(argv[0]);
        mx_printstr(" [filename]\n");
        exit(EXIT_FAILURE);
    }
}

static void file_not_exist_error(char *argv[]) {
	int descriptor = open(argv[1], O_RDONLY);

    if (descriptor == -1) {
        mx_printstr("error: file ");
        mx_printstr(argv[1]);
        mx_printstr(" does not exist\n");
        exit(EXIT_FAILURE);
    }

	close(descriptor);
}

static void empty_file_error(char *argv[]) {
    char *file_content = mx_file_to_str(argv[1]);

    if (file_content[0] == '\0') {
        mx_printstr("error: file ");
        mx_printstr(argv[1]);
        mx_printstr(" is empty\n");

        free(file_content);
        exit(EXIT_FAILURE);
    }

    free(file_content);
}


void errors(int argc, char *argv[]) {
	usage_error(argc, argv);
	file_not_exist_error(argv);
	empty_file_error(argv);
}