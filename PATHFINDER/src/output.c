#include "../inc/pathfinder.h"

static void print_separator(void) {
    for (int i = 0; i < 40; ++i) {
        mx_printchar('=');
    }
    mx_printchar('\n');
}

static void print_path(int *path, int path_length, Island *islands, int **matrix) {
    mx_printstr("Path: ");
    mx_printstr(islands[path[1]].name);
    mx_printstr(" -> ");
    mx_printstr(islands[path[0]].name);
    mx_printchar('\n');
    mx_printstr("Route: ");

    for (int i = 1; i < path_length + 1; i++) {
        mx_printstr(islands[path[i]].name);
        if (i < path_length) {
            mx_printstr(" -> ");
        }
    }

    mx_printstr("\nDistance: ");
    int path_dist = 0;

    for (int i = 1; i < path_length; i++) {
        int between = matrix[path[i]][path[i + 1]];
        mx_printint(between);
        path_dist += between;
        if (i < path_length - 1) {
            mx_printstr(" + ");
        }
    }

    if (path_length != 2) {
        mx_printstr(" = ");
        mx_printint(path_dist);
    }

    mx_printchar('\n');
}

static void dfs(int **matrix, int **shortest_paths, int *path, int path_length, int size, Island *islands) {
	int start = path[0];
	int end = path[path_length];

	for (int i = 0; i < size; i++) {
		if ((matrix[end][i] == shortest_paths[end][start] - shortest_paths[i][start]) && i != path[path_length]) {
			path_length++;
			path[path_length] = i;
			dfs(matrix, shortest_paths, path, path_length, size, islands);
			path_length--;
		}
	}

	if (path[path_length] != start) return;

	print_separator();
	print_path(path, path_length, islands, matrix);
	print_separator();
}

void output(int **matrix, int **shortest_paths, int size, Island *islands) {
    int *path = (int*)malloc((size + 1) * sizeof(int));
    int path_length = 1;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            path[1] = i;
            path[0] = j;
            dfs(matrix, shortest_paths, path, path_length, size, islands);
        }
    }

    free(path);
}
