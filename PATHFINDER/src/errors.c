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
    char *str = mx_file_to_str(argv[1]);
    char **strarr = mx_strsplit(str, '\n');

    for (int i = 0; i < mx_strlen(strarr[0]); i++) {
        if (!mx_isdigit(strarr[0][i])) {
            mx_printerr("error: line 1 is not valid\n");
            exit(1);
        }
    }
    if (mx_atoi(strarr[0]) <= 0) {
        mx_printerr("error: line 1 is not valid\n");
        exit(1); 
    }

    mx_strdel(&str);
    mx_del_strarr(&strarr);
}

static void check_line(char *str, int index) {
    for (int i = 0; i < mx_strlen(str); i++) {
        if (!mx_isalpha(str[i])) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(index + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
    }
}

void invalid_line_error(char *argv[]) {
    char *str = mx_file_to_str(argv[1]);
    char **strarr = mx_strsplit(str, '\n');

    for (int i = 1; strarr[i]; i++) {
        if (mx_get_char_index(strarr[i], '-') < 0 || mx_get_char_index(strarr[i], ',') < 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }
        if (mx_count_substr(strarr[i], "-") > 1 || mx_count_substr(strarr[i], ",") > 1) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        char **str_arr = mx_strsplit(strarr[i], '-');

        check_line(str_arr[0], i);
        
        check_line(mx_strndup(str_arr[1], mx_get_char_index(str_arr[1] ,',')), i);

        for (int j = mx_get_char_index(str_arr[1] ,',') + 1; j < mx_strlen(str_arr[1]); j++) {
            if(!mx_isdigit(str_arr[1][j])) {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i + 1));
                mx_printerr(" is not valid\n");
                exit(1);
            }
        }

        if (mx_strcmp(str_arr[0], mx_strndup(str_arr[1], mx_get_char_index(str_arr[1] ,','))) == 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(1);
        }

        mx_strdel(&str);
        mx_del_strarr(&str_arr);
    }
}



void errors(int argc, char *argv[]) {
	usage_error(argc, argv);
	file_not_exist_error(argv);
	empty_file_error(argv);
}