#include "uls.h"

bool mx_output_directory(t_element *element_data, t_flags *flags, bool mx_element_name_output) {
    if (mx_element_name_output) {
        mx_printstr(element_data->name);
        mx_printstr(":\n");
    }

    t_list *elements_data = NULL;
    bool result = mx_take_dir_info(&elements_data, element_data->path, flags);

    if (flags->format == L_OUTPUT
        && elements_data != NULL) {
        mx_printstr("total ");
        mx_printint(mx_block_num(elements_data));
        mx_printchar('\n');
    }

    if (!result) {
        mx_error_output(element_data->name);
        return false;
    }

    mx_sort_by_parameters(elements_data, flags->sort_type, flags->is_rev);
    mx_output_type(elements_data, flags);

    if (flags->is_R) {
        t_list *directories = NULL;

        while (elements_data != NULL) {
            t_element *entry = elements_data->data;

            if (S_ISDIR(entry->stat.st_mode)
                && !mx_is_hidden(entry->name, DOTS)) {
                free(entry->name);
                entry->name = mx_strdup(entry->path);
                mx_push_back(&directories, entry);
            }

            elements_data = elements_data->next;
        }

        if (directories != NULL) {
            mx_printchar('\n');
        }

        if (!mx_output_directories(directories, flags, true)) {
            result = false;
        }

        mx_clear_list(&directories);
    }

    mx_free_elements(elements_data);

    return result;
}
