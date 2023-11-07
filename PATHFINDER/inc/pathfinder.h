#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <libmx.h>
#include <stdlib.h>

#define INT_MAX 2147483647

typedef struct s_islands {
    int file;
    int words;
    int n_islands;
    char *file_in_str;
    char **unique_islands;
    char **islands;
} t_islands;

typedef struct s_matrix {
    int len;
    int *route;
    long **first;
    long **table;
} t_matrix;

// Errors
void usage_error(int argc);
void file_not_found(const char *filename);
void empty_file(const char *filename);
void invalid_first_line(const char *filename);
void invalid_line(const char *filename);
void invalid_islands(const char *filename);
void duplicate_bridges(const char *filename);
void lengths_sum(const char *filename);

void mx_floyd_marshall(t_islands *path, t_matrix *matrix);
void create_islands(t_islands *path, t_matrix *matrix);
void output(t_islands *path, t_matrix *matrix);
char **vertex(char *str, int size);
int extract_size(const char *str);

void clean_memory_matrix(t_islands *path, t_matrix *matrix);
void clean_memory_path(t_islands *path);


#endif
