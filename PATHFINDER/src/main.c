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

void floyd_warshall(Graph *graph) {
    for (int k = 0; k < graph->num_vertices; ++k) {
        for (int i = 0; i < graph->num_vertices; ++i) {
            for (int j = 0; j < graph->num_vertices; ++j) {
                if (graph->adj_matrix[i][k] != 0 && graph->adj_matrix[k][j] != 0) {
                    int new_dist = graph->adj_matrix[i][k] + graph->adj_matrix[k][j];
                    if (graph->adj_matrix[i][j] == 0 || new_dist < graph->adj_matrix[i][j]) {
                        graph->adj_matrix[i][j] = new_dist;
                    }

					if (i == j) {
						graph->adj_matrix[i][j] = 0;
					}
                }
            }
        }
    }
}

void print_shortest_paths(Graph *graph, Island *islands) {
    for (int i = 0; i < graph->num_vertices; ++i) {
        for (int j = i + 1; j < graph->num_vertices; ++j) {
            if (graph->adj_matrix[i][j] != 0) {
                printf("========================================\n");
                printf("Path: %s -> %s\n", islands[i].name, islands[j].name);
                printf("Route: %s", islands[i].name);
                int next_vertex = i;
                while (next_vertex != j) {
                    for (int k = 0; k < graph->num_vertices; ++k) {
                        if (graph->adj_matrix[next_vertex][j] == graph->adj_matrix[next_vertex][k] + graph->adj_matrix[k][j]) {
                            next_vertex = k;
                            printf(" -> %s", islands[k].name);
                            break;
                        }
                    }
                }
                printf("\nDistance: ");
                printf("%d", graph->adj_matrix[i][j]);
                printf("\n");
            }
        }
    }
}


int mx_sscanf(const char *str, const char *format, char *start, char *end, int *weight) {
   int parsed_values = 0;

    if (start) {
        *start = '\0';
    }
    if (end) {
        *end = '\0';
    }

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                int i = 0;
                char *city = (parsed_values == 0 && start) ? start : end;
                while (*str != '\0' && *str != ' ' && *str != ',' && *str != '-') {
                    if (city) {
                        city[i] = *str;
                    }
                    i++;
                    str++;
                }
                if (city) {
                    city[i] = '\0';
                }
                parsed_values++;
            } else if (*format == 'd') {
                *weight = 0;
                while (*str >= '0' && *str <= '9') {
                    *weight = *weight * 10 + (*str - '0');
                    str++;
                }
                parsed_values++;
            }
        } else {
            if (*str != *format) {
                return parsed_values;
            }
            str++;
        }
        format++;
    }

    return parsed_values;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return 1;
    }


    char *file = mx_file_to_str(argv[1]);

	char *line = mx_strtok((char*)file, "\n");
	int verticies = mx_atoi(line);

	Island* islands = (Island*)malloc(verticies * sizeof(Island));
	int num_islands = 0;

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


		// ------ Get start index
		int start_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, edge.start) == 0) {
                start_index = i;
                break;
            }
		}

		if (start_index == -1) {
			islands[num_islands].name = mx_strdup(edge.start);
			start_index = num_islands;
			islands[num_islands].index = start_index;
			num_islands++;
		}

		// ------ Get end index
		int end_index = -1;
		for (int i = 0; i < num_islands; i++) {
			if (mx_strcmp(islands[i].name, edge.end) == 0) {
                end_index = i;
                break;
            }
		}

		if (end_index == -1) {
			islands[num_islands].name = mx_strdup(edge.end);
			end_index = num_islands;
			islands[num_islands].index = end_index;
			num_islands++;
		}



		graph->adj_matrix[start_index][end_index] = edge.weight;
		graph->adj_matrix[end_index][start_index] = edge.weight;
	}

	floyd_warshall(graph);

	print_shortest_paths(graph, islands);

	free(graph);
    

    return 0;
}