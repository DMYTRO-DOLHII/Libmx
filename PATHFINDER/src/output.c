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

    for (int i = 0; i < path_length; i++) {
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

// static void dfs(Graph *graph, Island *islands, int current, int destination, int *path, int path_length, int **shortest_paths) {
//     islands[current].visited = true;
//     path[path_length] = current;

//     if (current == destination) {
//         print_path(islands, path, path_length + 1, graph);
// 		return;
//     } else {
//         for (int i = 0; i < graph->num_vertices; ++i) {
//             if (graph->adj_matrix[current][i] != INF && !islands[i].visited) {
//                 dfs(graph, islands, i, destination, path, path_length + 1, shortest_paths);
//             }
//         }
//     }

// 	islands[current].visited = false;
// }

static void dfs(Graph *graph, Island *islands, int current, int destination, int *path, int path_length, int **shortest_paths) {
	int start = path[0];
	int end = path[path_length];

	for (int i = 0; i < graph->num_vertices; i++) {
		if ((graph->adj_matrix[end][i] == shortest_paths[end][start] - shortest_paths[i][start]) && i != path[path_length]) {
			path_length++;
			path[path_length] = i;
			dfs(graph, islands, current, destination, path, path_length, shortest_paths);
			path_length--;
		}
	}

	if (path[path_length] != start) return;

	print_separator();
	print_path(path, path_length, islands, graph->adj_matrix);
	print_separator();
}

void output(Graph *graph, Island *islands, int **shortest_paths, int point_a, int point_b) {
    if (point_a < 0 || point_a >= graph->num_vertices || point_b < 0 || point_b >= graph->num_vertices) {
        return;
    }

    int distance = shortest_paths[point_a][point_b];

    if (distance == 0) {
        return;
    }

    int *path = (int *)malloc(graph->num_vertices * sizeof(int));

	path[1] = point_a;
	path[0] = point_b;

    dfs(graph, islands, point_a, point_b, path, 0, shortest_paths);
    free(path);
}
