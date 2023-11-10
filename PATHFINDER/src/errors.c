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
    int descriptor = open(argv[1], O_RDONLY);

	char buffer[1];
	int bytes_read = read(descriptor, buffer, sizeof(buffer));

    if (bytes_read <= 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(1);
    }

    close(descriptor);
}

static void invalid_first_line_error(char *argv[]) {
    char *file_content = mx_file_to_str(argv[1]);
    char *first_line = mx_strtok(file_content, "\n");

    if (!mx_isdigit_str(first_line) || mx_atoi(first_line) <= 0) {
        mx_printstr("error: line 1 is not valid\n");

        free(file_content);
        exit(EXIT_FAILURE);
    }

    free(file_content);
}

static void ivalid_line_error(char *argv[]) {
	
}


void errors(int argc, char *argv[]) {
	usage_error(argc, argv);
	file_not_exist_error(argv);
	empty_file_error(argv);
}