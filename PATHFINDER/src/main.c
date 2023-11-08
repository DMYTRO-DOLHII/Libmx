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

Island* create_island(const char *name, int index) {
    Island *island = (Island*)malloc(sizeof(Island));
    island->name = mx_strdup(name);
    island->index = index;
    return island;
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

void add_edge(Graph *graph, Edge edge, Island *islands) {
    int start_index = islands[edge.start[0] - 'A'].index;
    int end_index = islands[edge.end[0] - 'A'].index;
    graph->adj_matrix[start_index][end_index] = edge.weight;
    graph->adj_matrix[end_index][start_index] = edge.weight;
}

void print_graph(Graph *graph, Island *islands) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        for (int j = 0; j < graph->num_vertices; ++j) {
            char num_str[12]; // Assuming bridge length can be represented in 11 characters
            snprintf(num_str, sizeof(num_str), "%d ", graph->adj_matrix[i][j]);
            mx_printstr(num_str);
        }
        mx_printstr("\n");
    }
}

int main() {
    char input[] = "8\nKyiv-Kharkiv,471\nNikopol-Kharkiv,340\nKyiv-Warsaw,766\nKyiv-Paris,2403\nKyiv-Prague,1141\nKyiv-Singapore,11864\nKyiv-Tokyo,11079\n";

    char *line = strtok(input, "\n");
    int num_islands = atoi(line);

    Island islands[num_islands];
    for (int i = 0; i < num_islands; ++i) {
        char island_name[2] = {(char)('A' + i), '\0'}; // Single-letter island names A, B, C, ...
        islands[i] = *create_island(island_name, i);
    }

    Graph *graph = create_graph(num_islands);

    line = strtok(NULL, "\n"); // Move to the first edge
    while (line != NULL) {
        Edge edge;
        char *dash_pos = mx_strchr(line, '-');
        char *comma_pos = mx_strchr(line, ',');
        int start_len = dash_pos - line;
        int end_len = comma_pos - dash_pos - 1;

        edge.start = mx_strndup(line, start_len);
        edge.end = mx_strndup(dash_pos + 1, end_len);
        edge.weight = atoi(comma_pos + 1);

        add_edge(graph, edge, islands);

        free(edge.start);
        free(edge.end);

        line = mx_strtok(NULL, "\n"); // Move to the next edge
    }

    mx_printstr("Adjacency Matrix:\n");
    print_graph(graph, islands);

    // Free memory
    for (int i = 0; i < num_islands; ++i) {
        free(islands[i].name);
    }
    free(graph->adj_matrix);
    free(graph);

    return 0;
}
