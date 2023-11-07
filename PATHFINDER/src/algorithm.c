#include "../inc/pathfinder.h"

void mx_floyd_marshall(t_islands *path, t_matrix *matrix) {
    long sum;
    int i;

    for (i = 0; i < path->n_islands; i++) {
        for (int j = i; j < path->n_islands; j++) {
            matrix->first[i][j] = matrix->table[i][j];
            matrix->first[j][i] = matrix->table[j][i];
        }
    }
    for (int k = 0; k < path->n_islands; k++) {
        for (i = 0; i < path->n_islands; i++) {
            for (int j = i + 1; j < path->n_islands; j++) {
                sum = matrix->table[k][j] + matrix->table[i][k];
                if (matrix->table[i][j] > sum) {
                    matrix->table[i][j] = sum;
                    matrix->table[j][i] = sum;
                }
            }
        }
    }
}
