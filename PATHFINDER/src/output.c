#include "../inc/pathfinder.h"

static void floyd_warshall_path(Graph *graph, int *route, int len) {
    int num_vertices = graph->num_vertices;

    // Initialize the path matrix with the initial route
    int path[num_vertices][num_vertices];
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            path[i][j] = -1;  // Indicates no intermediate vertex
        }
    }

    // Set the initial path matrix based on the given route
    for (int i = 0; i < len - 1; ++i) {
        path[route[i]][route[i + 1]] = route[i];
    }

    // Floyd-Warshall algorithm to find shortest paths and intermediate vertices
    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                if (graph->adj_matrix[i][k] != 0 && graph->adj_matrix[k][j] != 0) {
                    int new_dist = graph->adj_matrix[i][k] + graph->adj_matrix[k][j];
                    if (graph->adj_matrix[i][j] == 0 || new_dist < graph->adj_matrix[i][j]) {
                        graph->adj_matrix[i][j] = new_dist;
                        path[i][j] = k;
                    }
                }
            }
        }
    }

    // Reconstruct the intermediate vertices for the given route
    int start = route[0];
    int end = route[len - 1];
    int intermediate = path[start][end];
    int count = 1;

    while (intermediate != -1) {
        route[len - count] = intermediate;
        intermediate = path[start][intermediate];
        ++count;
    }
}

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
