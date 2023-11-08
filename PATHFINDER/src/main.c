#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/pathfinder.h"

typedef struct {
    int num_vertices;
    int **adj_matrix;
} Graph;

typedef struct {
    int start_vertex;
    int end_vertex;
    int weight;
} Edge;

Graph* create_graph(int num_vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_matrix = (int**)malloc(num_vertices * sizeof(int*));

    for (int i = 0; i < num_vertices; ++i) {
        graph->adj_matrix[i] = (int*)malloc(num_vertices * sizeof(int));
        memset(graph->adj_matrix[i], 0, num_vertices * sizeof(int));
    }

    return graph;
}

Edge parse_edge(char *line) {
    Edge edge;
    char *token = strtok(line, "-,");
    edge.start_vertex = atoi(token);

    token = strtok(NULL, "-,");
    edge.end_vertex = atoi(token);

    token = strtok(NULL, "-,");
    edge.weight = atoi(token);

    return edge;
}

void add_edge(Graph *graph, Edge edge) {
    graph->adj_matrix[edge.start_vertex][edge.end_vertex] = edge.weight;
    graph->adj_matrix[edge.end_vertex][edge.start_vertex] = edge.weight;
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

void print_shortest_paths(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        for (int j = i + 1; j < graph->num_vertices; ++j) {
            if (graph->adj_matrix[i][j] != 0) {
                printf("========================================\n");
                printf("Path: %d -> %d\n", i, j);
                printf("Route: %d", i);
                int next_vertex = i;
                while (next_vertex != j) {
                    for (int k = 0; k < graph->num_vertices; ++k) {
                        if (graph->adj_matrix[next_vertex][j] == graph->adj_matrix[next_vertex][k] + graph->adj_matrix[k][j]) {
                            next_vertex = k;
                            printf(" -> %d", k);
                            break;
                        }
                    }
                }
                printf("\nDistance: %d\n", graph->adj_matrix[i][j]);
            }
        }
    }
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    char *file_content = mx_file_to_str(filename); // Use mx_file_to_str to read file content

    if (file_content == NULL) {
        perror("Error reading the file");
        exit(EXIT_FAILURE);
    }

    // Parse the file content into edges and create the graph
    int num_vertices;
    sscanf(file_content, "%d", &num_vertices);
    Graph *graph = create_graph(num_vertices);

    char *line = strtok(file_content, "\n");
    while ((line = strtok(NULL, "\n")) != NULL) {
        Edge edge = parse_edge(line);
        add_edge(graph, edge);
    }

    // Apply Floyd-Warshall algorithm to find shortest paths
    floyd_warshall(graph);

    // Print the shortest paths
    print_shortest_paths(graph);

    // Clean up: Free memory and close the file descriptor
    free_graph(graph);
    free(file_content); // Free the dynamically allocated file content
    return 0;
}
