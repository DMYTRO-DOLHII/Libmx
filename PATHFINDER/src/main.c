#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/pathfinder.h"

typedef struct {
    char *name;
    int index;
} Island;

typedef struct {
    int num_vertices;
    int **adj_matrix;
} Graph;

typedef struct {
    char *start;
    char *end;
    int weight;
} Edge;

void mx_printstr(const char *str) {
    while (*str) {
        putchar(*str);
        ++str;
    }
}

Graph* create_graph(int num_vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_matrix = (int**)malloc(num_vertices * sizeof(int*));

    for (int i = 0; i < num_vertices; ++i) {
        graph->adj_matrix[i] = (int*)malloc(num_vertices * sizeof(int));

        // Initialize matrix elements to 0 manually
        for (int j = 0; j < num_vertices; ++j) {
            graph->adj_matrix[i][j] = 0;
        }
    }

    return graph;
}

void add_edge(Graph *graph, Edge edge) {
    int start_index = edge.start[0] - 'A';
    int end_index = edge.end[0] - 'A';
    graph->adj_matrix[start_index][end_index] = edge.weight;
    graph->adj_matrix[end_index][start_index] = edge.weight;
}

void floyd_warshall(Graph *graph) {
    for (int k = 0; k < graph->num_vertices; ++k) {
        for (int i = 0; i < graph->num_vertices; ++i) {
            for (int j = 0; j < graph->num_vertices; ++j) {
                if (graph->adj_matrix[i][k] != 0 && graph->adj_matrix[k][j] != 0) {
                    int new_dist = graph->adj_matrix[i][k] + graph->adj_matrix[k][j];
                    if (graph->adj_matrix[i][j] == 0 || new_dist < graph->adj_matrix[i][j]) {
                        graph->adj_matrix[i][j] = new_dist;
                    }
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mx_printstr("usage: ./pathfinder [filename]\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        mx_printstr("Error: Cannot open file\n");
        return 1;
    }

    // Read number of vertices from the first line
    int num_vertices;
    fscanf(file, "%d\n", &num_vertices);

    // Initialize islands and graph
    Island islands[num_vertices];
    for (int i = 0; i < num_vertices; ++i) {
        char island_name[2] = {(char)('A' + i), '\0'};
        islands[i].name = mx_strdup(island_name);
        islands[i].index = i;
    }

    Graph *graph = create_graph(num_vertices);

    // Parse edges and fill the graph
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        Edge edge;
        char *dash_pos = mx_strtok(line, "-,");
        edge.start = mx_strdup(dash_pos);
        dash_pos = mx_strtok(NULL, "-,");
        edge.end = mx_strdup(dash_pos);
        char *comma_pos = mx_strtok(NULL, "-,");
        edge.weight = mx_atoi(comma_pos);

        add_edge(graph, edge);

        free(edge.start);
        free(edge.end);
    }

    fclose(file);

    // Apply Floyd-Warshall algorithm to find shortest paths
    floyd_warshall(graph);

    // Output shortest paths
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = i + 1; j < num_vertices; ++j) {
            if (graph->adj_matrix[i][j] != 0) {
                mx_printstr("========================================\n");
                mx_printstr("Path: ");
                mx_printstr(islands[i].name);
                mx_printstr(" -> ");
                mx_printstr(islands[j].name);
                mx_printstr("\nRoute: ");
                mx_printstr(islands[i].name);
                int next_vertex = i;
                while (next_vertex != j) {
                    for (int k = 0; k < num_vertices; ++k) {
                        if (graph->adj_matrix[next_vertex][j] == graph->adj_matrix[next_vertex][k] + graph->adj_matrix[k][j]) {
                            next_vertex = k;
                            mx_printstr(" -> ");
                            mx_printstr(islands[k].name);
                            break;
                        }
                    }
                }
                mx_printstr("\nDistance: ");
                mx_printint(graph->adj_matrix[i][j]);
                mx_printchar('\n');
            }
        }
    }

    // Free memory
    for (int i = 0; i < num_vertices; ++i) {
        free(islands[i].name);
    }
    for (int i = 0; i < num_vertices; ++i) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);

    return 0;
}
