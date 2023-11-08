#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

static void catch_errors(int argc, char *argv[]) {
	usage_error(argc);
	file_not_found(argv[1]);
	empty_file(argv[1]);
	invalid_first_line(argv[1]);
	invalid_line(argv[1]);
	invalid_islands(argv[1]);
	duplicate_bridges(argv[1]);
	lengths_sum(argv[1]);
}

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
    // Implement Floyd-Warshall algorithm
}

void print_shortest_paths(Graph *graph) {
    // Implement printing shortest paths
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

    catch_errors(argc, argv);

    const char *filename = argv[1];
    int file_descriptor = open(filename, O_RDONLY);

    if (file_descriptor == -1) {
        perror("Error opening the file");
        exit(EXIT_FAILURE);
    }

    char buffer[4096]; // Buffer to store the file content
    int bytes_read;

    bytes_read = read(file_descriptor, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("Error reading the file");
        close(file_descriptor);
        exit(EXIT_FAILURE);
    }

    // Parse the file content into edges and create the graph
    int num_vertices;
    sscanf(buffer, "%d", &num_vertices);
    Graph *graph = create_graph(num_vertices);

    char *line = strtok(buffer, "\n");
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
    close(file_descriptor);

    return 0;
}
