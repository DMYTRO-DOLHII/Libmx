#include "uls.h"

bool mx_output_directories(t_list *directories, t_flags *flags, bool print_objects_names) {
    bool ret = true;
    mx_sort_by_parameters(directories, flags->sort_type, flags->is_rev);

    while (directories != NULL) {
        t_element *element_data = directories->data;

        if (!mx_output_directory(element_data, flags, print_objects_names)) {
            ret = false;
        }

        if (directories->next != NULL) {
            mx_printchar('\n');
        }

        directories = directories->next;
    }

    return ret;
}
