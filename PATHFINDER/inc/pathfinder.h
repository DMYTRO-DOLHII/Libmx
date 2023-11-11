#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"
#include <stdlib.h>

#define INT_MAX 2147483647
#define INF 9999999

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

Graph* create_graph(int num_vertices);
int island_index(Island *islands, int size, char *name);
int mx_sscanf(const char *str, const char *format, char *start, char *end, int *weight);
void output(int **matrix, int **shortest_paths, int size, Island *islands);
void errors(int argc, char *argv[]);

#endif
