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
	mx_printstr("\n--- Itaration ---\n");
	mx_printint(start_index);
	mx_printint(end_index);
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
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error: Cannot open file");
        return 1;
    }

    // Read the number of vertices from the first line
    char numVerticesStr[10]; // Assuming the number of vertices won't exceed 10 digits
    ssize_t bytesRead = read(fd, numVerticesStr, sizeof(numVerticesStr));
    if (bytesRead <= 0) {
        perror("Error: Unable to read the number of vertices");
        close(fd);
        return 1;
    }

    int numVertices = atoi(numVerticesStr);
    printf("Number of Vertices: %d\n", numVertices);

    // Read the file line by line to extract edges
    char buffer[100];
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the buffer
        char *line = buffer;

        // Extract edges from the line and process them
        char *dashPos = strtok(line, "-,");
        char *start = dashPos;
        dashPos = strtok(NULL, "-,");
        char *end = dashPos;
        char *weightStr = strtok(NULL, "-,\n");
        int weight = atoi(weightStr);

        // Process the extracted edge (start, end, weight)
        printf("Edge: %s -> %s, Weight: %d\n", start, end, weight);
    }

    if (bytesRead == -1) {
        perror("Error: Cannot read file");
    }

    close(fd);
    return 0;
}