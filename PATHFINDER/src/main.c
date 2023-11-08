#include "../inc/pathfinder.h"

typedef struct {
    int num_vertices;
    int **adj_matrix;
} Graph;

typedef struct {
    char *start_vertex_name;
    char *end_vertex_name;
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

        // Initialize matrix elements to 0 manually
        for (int j = 0; j < num_vertices; ++j) {
            graph->adj_matrix[i][j] = 0;
        }
    }

    return graph;
}

Edge parse_edge(char *line) {
    Edge edge;
    char *token = mx_strtok(line, "-,");
    edge.start_vertex_name = strdup(token);
    edge.start_vertex = mx_atoi(token);

    token = mx_strtok(NULL, "-,");
    edge.end_vertex_name = strdup(token);
    edge.end_vertex = mx_atoi(token);

    token = mx_strtok(NULL, "-,");
    edge.weight = mx_atoi(token);

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
                mx_printstr("========================================\n");
                mx_printstr("Path: ");
                mx_printstr(graph->adj_matrix[i][j]->start_vertex_name);
                mx_printstr(" -> ");
                mx_printstr(graph->adj_matrix[i][j]->end_vertex_name);
                mx_printstr("\nRoute: ");
                mx_printint(i);
                int next_vertex = i;
                while (next_vertex != j) {
                    for (int k = 0; k < graph->num_vertices; ++k) {
                        if (graph->adj_matrix[next_vertex][j] == graph->adj_matrix[next_vertex][k] + graph->adj_matrix[k][j]) {
                            next_vertex = k;
                            mx_printstr(" -> ");
                            mx_printint(k);
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
}

void free_graph(Graph *graph) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        free(graph->adj_matrix[i]->start_vertex_name);
        free(graph->adj_matrix[i]->end_vertex_name);
        free(graph->adj_matrix[i]);
    }
    free(graph->adj_matrix);
    free(graph);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        mx_printerr("Usage: <inputfile>");
        return 1;
    }

    const char *filename = argv[1];
    char *file_content = mx_file_to_str(filename); // Use mx_file_to_str to read file content

    if (file_content == NULL) {
        mx_printerr("Error: Cannot read file\n");
        return 1;
    }

    // Extract number of vertices
    int num_vertices;
    num_vertices = mx_atoi(file_content);
    while (*file_content != '\n') {
        file_content++;
    }
    file_content++; // Move past the newline character

    // Parse edges and create graph
    Graph *graph = create_graph(num_vertices);
    while (*file_content != '\0') {
        Edge edge = parse_edge(file_content);
        add_edge(graph, edge);
        while (*file_content != '\n' && *file_content != '\0') {
            file_content++;
        }
        if (*file_content == '\n') {
            file_content++; // Move past the newline character
        }
    }

    // Apply Floyd-Warshall algorithm to find shortest paths
    floyd_warshall(graph);

    // Print the shortest paths
    print_shortest_paths(graph);

    // Clean up: Free memory
    free_graph(graph);
    free(file_content);

    return 0;
}
