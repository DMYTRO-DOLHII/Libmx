#include "uls.h"

int mx_output_elements(t_list *elements, t_flags *flags) {
    t_list *files = NULL;
    t_list *directories = NULL;
    bool print_elements_names = mx_list_size(elements) > 1;
    int result = 0;
    mx_arrange_elements(elements, flags->sort_type);

    while (elements != NULL) {
        char *object = elements->data;
        elements = elements->next;
        t_element *element_data = mx_init_element_data(NULL, object, flags);

        if (element_data == NULL) {
            mx_error_output(object);
            result = 1;
            continue;
        }

        if (S_ISDIR(element_data->stat.st_mode)) {
            mx_push_back(&directories, element_data);
        } else {
            mx_push_back(&files, element_data);
        }
    }

    mx_output_files(files, flags);

    if (files != NULL
        && directories != NULL) {
        mx_printchar('\n');
    }

    if (!mx_output_directories(directories, flags, print_elements_names)) {
        result = 1;
    }

    mx_free_elements(files);
    mx_free_elements(directories);

    return result;
}
