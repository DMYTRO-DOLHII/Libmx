#include "../inc/pathfinder.h"

// ------------------------------------------------
static void usage_error(int argc, char *argv[]) {
    if (argc != 2) {
        mx_printstr("usage: ");
        mx_printstr(argv[0]);
        mx_printstr(" [filename]\n");
        exit(EXIT_FAILURE);
    }
}
// ------------------------------------------------


// ------------------------------------------------
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
// ------------------------------------------------


// ------------------------------------------------
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
// ------------------------------------------------


// ------------------------------------------------
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
// ------------------------------------------------


// ------------------------------------------------
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
// ------------------------------------------------


// ------------------------------------------------
static void invalid_islands_error(char *argv[]) {;
    char *content = mx_file_to_str(argv[1]);
	char *line = mx_strtok(content, "\n");

    int verticies = mx_atoi(line);

	Island* islands = (Island*)malloc(verticies * sizeof(Island));
	int num_islands = 0;

	while ((line = mx_strtok(NULL, "\n")) != NULL) {
        char start[100];
        char end[100];
        int weight;

        int r = mx_sscanf(line, "%s-%s,%d", start, end, &weight);

        if (r != 3) {
            continue;
        }

		// ------ Get start index
		int start_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, start) == 0) {
                start_index = i;
                break;
            }
		}

		if (start_index == -1) {
			islands[num_islands].name = mx_strdup(start);
			start_index = num_islands;
			islands[num_islands].index = start_index;
			num_islands++;
		}

		// ------ Get end index
		int end_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, end) == 0) {
                end_index = i;
                break;
            }
		}

		if (end_index == -1) {
			islands[num_islands].name = mx_strdup(end);
			end_index = num_islands;
			islands[num_islands].index = end_index;
			num_islands++;
		}

    }

    if (verticies != num_islands) {
        mx_printerr("error: invalid number of islands\n");
        exit(-1);
    }

    free(islands);
}
// ------------------------------------------------


// ------------------------------------------------
static void duplicate_bridges_error(char *argv[]) {
    char *content = mx_file_to_str(argv[1]);
    char *line = mx_strtok(content, "\n");
    int verticies = mx_atoi(line);


    Graph* graph = create_graph(verticies);
	Island* islands = (Island*)malloc(verticies * sizeof(Island));
	int num_islands = 0;

    int **bridges_matrix = (int **)malloc(verticies * sizeof(int *));
    for (int i = 0; i < verticies; ++i) {
        bridges_matrix[i] = (int *)malloc(verticies * sizeof(int));
        for (int j = 0; j < verticies; ++j) {
            bridges_matrix[i][j] = 0;
        }
    }

	// Fill adjecency matrix
    while ((line = mx_strtok(NULL, "\n")) != NULL) {
        char start[100];
        char end[100];
        int weight;

        int r = mx_sscanf(line, "%s-%s,%d", start, end, &weight);

        if (r != 3) {
            continue;
        }

		// ------ Get start index
		int start_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, start) == 0) {
                start_index = i;
                break;
            }
		}

		if (start_index == -1) {
			islands[num_islands].name = mx_strdup(start);
			start_index = num_islands;
			islands[num_islands].index = start_index;
			num_islands++;
		}

		// ------ Get end index
		int end_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, end) == 0) {
                end_index = i;
                break;
            }
		}

		if (end_index == -1) {
			islands[num_islands].name = mx_strdup(end);
			end_index = num_islands;
			islands[num_islands].index = end_index;
			num_islands++;
		}

		graph->adj_matrix[start_index][end_index] = weight;
		graph->adj_matrix[end_index][start_index] = weight;
    }

	// Check for duplicate bridges
	char **strarr = mx_strsplit(line, '\n');
    for (int i = 1; strarr[i]; i++) {
        char* token = mx_strtok(line, "-,");
		char* start = mx_strdup(token);

		token = mx_strtok(line, "-,");
		char* end = mx_strdup(token);

		mx_printstr(start);
		mx_printstr(end);
		mx_printstr("\n");
        

        if (bridges_matrix[island_index(islands, num_islands, start)][island_index(islands, num_islands, end)] == 1 &&
			bridges_matrix[island_index(islands, num_islands, end)][island_index(islands, num_islands, start)] == 1) {
            mx_printerr("error: duplicate bridges\n");
            exit(-1);
        }

        bridges_matrix[island_index(islands, num_islands, start)][island_index(islands, num_islands, end)] = 1;
        bridges_matrix[island_index(islands, num_islands, end)][island_index(islands, num_islands, start)] = 1;
        mx_strdel(&start);
        mx_strdel(&end);
    }

    // Free the allocated memory
    free(content);
    for (int i = 0; i < verticies; ++i) {
        free(bridges_matrix[i]);
    }
    free(bridges_matrix);
	free(islands);
}
// ------------------------------------------------


// ------------------------------------------------
void sum_of_lengths_error(char *argv[]) {
    char *str = mx_file_to_str(argv[1]);
    long long int sum = 0;
    long long int max_length = INT_MAX;

    char* token = mx_strtok(str, ",");
    int first = 1;

    while(token != NULL) {
        if(first) {
            first = 0;
        } else {
            sum += mx_atoll(token);
        }

        token = mx_strtok(NULL, ",\n");
    }
    
    if (sum > max_length) {
        mx_printerr("error: sum of bridges lengths is too big");
        exit(1);
    }
}
// ------------------------------------------------

// ------------------------------------------------
void errors(int argc, char *argv[]) {
	usage_error(argc, argv);
	file_not_exist_error(argv);
	empty_file_error(argv);
	invalid_first_line_error(argv);
	invalid_line_error(argv);
	invalid_islands_error(argv);
	duplicate_bridges_error(argv);
	sum_of_lengths_error(argv);
}
// ------------------------------------------------

