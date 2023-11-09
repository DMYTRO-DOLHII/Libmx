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

    char *file = mx_file_to_str(argv[1]);

	char *line = mx_strtok((char*)file, "\n");
	int verticies = mx_atoi(line);

	Graph* graph = create_graph(verticies);

	while ((line = mx_strtok(NULL, "\n")) != NULL) {
		char start[100];
		char end[100];
		int weight;

		int r = mx_sscanf(line, "%s-%s,%d", start, end, &weight);

		if (r != 3) {
			mx_printstr("Extraction failed...");
		}

		Edge edge;

		edge.start = mx_strdup(start);
		edge.end = mx_strdup(end);
		edge.weight = weight;

		add_edge(graph, edge);
	}
    

    return 0;
}