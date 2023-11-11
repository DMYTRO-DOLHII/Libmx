#include "../inc/pathfinder.h"

Graph* create_graph(int num_vertices) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adj_matrix = (int**)malloc(num_vertices * sizeof(int*));

    for (int i = 0; i < num_vertices; ++i) {
        graph->adj_matrix[i] = (int*)malloc(num_vertices * sizeof(int));

        // Initialize matrix elements to 0 manually
        for (int j = 0; j < num_vertices; ++j) {
            graph->adj_matrix[i][j] = INF;
        }
    }

    return graph;
}

