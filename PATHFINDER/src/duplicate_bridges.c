#include "../inc/pathfinder.h"

void duplicate_bridges(const char *filename) {
    char *str = mx_file_to_str(filename);
    int size = extract_size(str);
    char **vertex_arr = vertex(str, size);
    int **test_m = (int **) malloc((size + 1) * sizeof(int *));
    for(int i = 0; i < size; i++) {
        test_m[i] = (int*)malloc(size * sizeof(int));
    }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            test_m[i][j] = 0;
        }
    }

    char **strarr = mx_strsplit(str, '\n');
    for (int i = 1; strarr[i]; i++) {
        char *from = mx_strndup(strarr[i], mx_get_char_index(strarr[i], '-'));
        strarr[i] += mx_get_char_index(strarr[i], '-') + 1;
        
        char *to = mx_strndup(strarr[i], mx_get_char_index(strarr[i], ','));
        strarr[i] += mx_get_char_index(strarr[i], ',') + 1;
        

        if (test_m[mx_index(vertex_arr, from)][mx_index(vertex_arr, to)] == 1 && test_m[mx_index(vertex_arr, to)][mx_index(vertex_arr, from)] == 1) {
            mx_printerr("error: duplicate bridges\n");
            exit(1);
        }

        test_m[mx_index(vertex_arr, from)][mx_index(vertex_arr, to)] = 1;
        test_m[mx_index(vertex_arr, to)][mx_index(vertex_arr, from)] = 1;
        mx_strdel(&from);
        mx_strdel(&to);
    }
    for(int i = 0; i < size; i++){
        free(test_m[i]);
    }
    free(test_m);
}