#include "uls.h"

void mx_output_files(t_list *files, t_flags *flags) {
    if (files != NULL) {
        mx_sort_by_parameters(files, flags->sort_type, flags->is_rev);
        mx_output_type(files, flags);
    }
}
