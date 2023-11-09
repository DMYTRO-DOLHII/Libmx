#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void floyd_warshall(Graph *graph, int ***shortest_paths) {
    int num_vertices = graph->num_vertices;

    *shortest_paths = (int **)malloc(num_vertices * sizeof(int *));
    for (int i = 0; i < num_vertices; ++i) {
        (*shortest_paths)[i] = (int *)malloc(num_vertices * sizeof(int));

        for (int j = 0; j < num_vertices; ++j) {
            (*shortest_paths)[i][j] = graph->adj_matrix[i][j];
        }
    }

    for (int k = 0; k < num_vertices; ++k) {
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = 0; j < num_vertices; ++j) {
                if ((*shortest_paths)[i][k] != INF && (*shortest_paths)[k][j] != INF) {
                    int new_dist = (*shortest_paths)[i][k] + (*shortest_paths)[k][j];
                    if ((*shortest_paths)[i][j] == INF || new_dist < (*shortest_paths)[i][j]) {
                        (*shortest_paths)[i][j] = new_dist;
                    }

                    if (i == j) {
                        (*shortest_paths)[i][j] = INF;
                    }
                }
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
			continue;
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

	int **shortest_pathes;

	floyd_warshall(graph, &shortest_pathes);

	// for (int i = 0; i < num_islands; i++) {
	// 	for (int j = i + 1; j < num_islands; j++) {
	// 		output(graph, islands, shortest_pathes, i, j);
	// 	}
	// }

	output(graph, islands, shortest_pathes, 0, 1);

	free(graph);
    

    return 0;
}