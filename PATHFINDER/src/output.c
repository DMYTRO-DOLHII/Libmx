#include "../inc/pathfinder.h"

static void mx_print_result(void) {
    for (int i = 0; i++ < 40; mx_printstr("="));
    mx_printstr("\n");
}

static bool validate_path(t_matrix *matrix, int k) {
    int i = matrix->route[matrix->len];
    int j = matrix->route[0];

    if (matrix->first[i][k] == matrix->table[i][j] - matrix->table[k][j])
        return true;
    return false;
}

static void print_path_route(t_islands *path, t_matrix *matrix) {
    mx_print_result();
    mx_printstr("Path: ");
    mx_printstr(path->unique_islands[matrix->route[1]]);
    mx_printstr(" -> ");
    mx_printstr(path->unique_islands[matrix->route[matrix->len]]);
    mx_printstr("\n");
    mx_printstr("Route: ");
    for (int i = 1; i < matrix->len + 1; ) {
        mx_printstr(path->unique_islands[matrix->route[i]]);
        ++i < matrix->len + 1 ? mx_printstr(" -> ") : mx_printstr("");
    }
    mx_printstr("\n");
}

static void print_distance(t_matrix *matrix) {
    int sum = 0;

    mx_printstr("Distance: ");
    for (int i = 1; i < matrix->len; i++){
        mx_printint(matrix->first[matrix->route[i]][matrix->route[i + 1]]);
        sum += matrix->first[matrix->route[i]][matrix->route[i + 1]];
        if (i < matrix->len - 1)
            mx_printstr(" + ");
        else if (i > 1) {
            mx_printstr(" = ");
            mx_printint(sum);
        }
    }
    mx_printstr("\n");
    mx_print_result();
}

static void print_path(t_islands *path, t_matrix *matrix) {
    for (int k = 0; k < path->n_islands; k++) {
        if (k != matrix->route[matrix->len]
            && validate_path(matrix, k)) {
            matrix->route[++matrix->len] = k;
            print_path(path, matrix);
            matrix->len--;
        }
    }
    if (matrix->route[matrix->len] != matrix->route[0])
        return;
    print_path_route(path, matrix);
    print_distance(matrix);
}

void output(t_islands *path, t_matrix *matrix) {
    for (int i = 0; i < path->n_islands; i++) {
        for (int j = i + 1; j < path->n_islands; j++) {
            matrix->route = (int *)malloc(sizeof(int) * (path->n_islands));
            matrix->len = 1;
            matrix->route[0] = j;
            matrix->route[matrix->len] = i;
            print_path(path, matrix);
            free(matrix->route);
        }
    }
}

