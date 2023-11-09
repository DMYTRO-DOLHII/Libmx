#include "../inc/pathfinder.h"

static void print_path_route(Island *islands, int *route, int len) {
    mx_printstr("Path: ");
    mx_printstr(islands[route[0]].name);
    mx_printstr(" -> ");
    mx_printstr(islands[route[len - 1]].name);
    mx_printstr("\nRoute: ");
    mx_printstr(islands[route[0]].name);
    for (int i = 1; i < len; ++i) {
        mx_printstr(" -> ");
        mx_printstr(islands[route[i]].name);
    }
    mx_printstr("\n");
}

static void print_distance(int **adj_matrix, int *route, int len) {
    int sum = 0;
    mx_printstr("Distance: ");
    for (int i = 0; i < len - 1; ++i) {
        sum += adj_matrix[route[i]][route[i + 1]];
        mx_printint(adj_matrix[route[i]][route[i + 1]]);
        if (i < len - 2) {
            mx_printstr(" + ");
        } else {
            mx_printstr(" = ");
            mx_printint(sum);
            mx_printstr("\n");
        }
    }
}

void print_shortest_paths(Graph *graph, Island *islands) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        for (int j = i + 1; j < graph->num_vertices; ++j) {
            if (graph->adj_matrix[i][j] != 0) {
                mx_printstr("========================================\n");
                int route[graph->num_vertices];
                route[0] = i;
                route[1] = j;
                floyd_warshall_path(graph, route, 2);
                print_path_route(islands, route, 2);
                print_distance(graph->adj_matrix, route, 2);
            }
        }
    }
}
