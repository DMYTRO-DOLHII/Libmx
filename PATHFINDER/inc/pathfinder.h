#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"
#include <stdlib.h>

#define INT_MAX 2147483647

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



void print_shortest_paths(Graph *graph, Island *islands);

#endif
