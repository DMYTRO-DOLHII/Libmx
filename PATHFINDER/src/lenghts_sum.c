#include "../inc/pathfinder.h"

void lengths_sum(const char *filename) {
    char *str = mx_file_to_str(filename);;
    long long int sum = 0;
    long long int max_length = INT_MAX;

    char* token = mx_strtok(str, ",");
    int first = 1;

    while(token != NULL) {
        if(first) {
            first = 0;
        } else {
            sum += mx_atoll(token);
        }

        token = mx_strtok(NULL, ",\n");
    }
    
    if (sum > max_length) {
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(1);
    }
}
