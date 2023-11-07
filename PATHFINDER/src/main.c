#include "../inc/pathfinder.h"

static void errors(int argc, char *argv[]) {
    usage_error(argc)
	file_not_found(argv[1])
	empty_file(argv[1])
	invalid_first_line(argv[1])
	invalid_line(argv[1])
	invalid_islands(argv[1])
	duplicate_bridges(argv[1])
	lengths_sum(argv[1])
}

int main(int argc, char *argv[]) {
    t_islands *path = (t_islands *)malloc(sizeof(t_islands));
    t_matrix *matrix = (t_matrix *)malloc(sizeof(t_matrix));

    errors(argc, argv);

    create_islands(path, matrix);
    mx_floyd_marshall(path, matrix);
    output(path, matrix);

    mx_del_strarr(&path->unique_islands);
    mx_del_strarr(&path->islands);
	
    clean_memory_matrix(path, matrix);
    clean_memory_path(path);

    return 0;
}
