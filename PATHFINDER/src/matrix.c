#include "../inc/pathfinder.h"

static void free_arr(int **arr, t_islands *path) {
    if (arr) {
        for (int i = 0; i < path->n_islands; i++)
            free(arr[i]);
        free(arr);
    }
}

static int get_island_index(char *island, t_islands *path) {
    for (int i = 0; path->unique_islands[i]; i++)
        if (!mx_strcmp(island, path->unique_islands[i]))
            return i;
    return 0;
}

void create_islands(t_islands *path, t_matrix *matrix) {
    int i;
    int j;
    char *buf = mx_strchr(path->file_in_str, ',');

    matrix->table = (long **)malloc(sizeof(long *) * path->n_islands);
    matrix->first = (long **)malloc(sizeof(long *) * path->n_islands);
    for (int i = 0; i < path->n_islands; i++) {
        matrix->table[i] = (long *)malloc(sizeof(long) * path->n_islands);
        matrix->first[i] = (long *)malloc(sizeof(long) * path->n_islands);
    }
    for (i = 0; i < path->n_islands; i++) {
        for (j = 0; j < path->n_islands; j++) {
            matrix->table[i][j] = (i != j ? INT_MAX : 0);
        }
    }
    for (int ai = 0 ; (buf = mx_strchr(buf, ',')); ai +=2) {
        i = get_island_index(path->islands[ai], path);
        j = get_island_index(path->islands[ai + 1], path);
        matrix->table[i][j] = mx_atoi(++buf);
        matrix->table[j][i] = matrix->table[i][j];
    }
}

void clean_memory_matrix(t_islands *path, t_matrix *matrix) {
    free_arr((int **)matrix->first, path);
    free_arr((int **)matrix->table, path);
    free(matrix);
}

void clean_memory_path(t_islands *path) {
    if (path->file_in_str)
        mx_strdel(&path->file_in_str);
    free(path);
}
