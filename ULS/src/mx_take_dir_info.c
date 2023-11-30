#include "uls.h"

bool mx_take_dir_info(t_list **objects, const char *name, t_flags *flags) {
    DIR *directory = opendir(name);
    struct dirent *object = NULL;

    if (directory == NULL) {
        return false;
    }

    while ((object = readdir(directory)) != NULL) {
        if (!mx_is_hidden(object->d_name, flags->ommit)) {
            mx_push_back(objects, mx_init_element_data(name, object->d_name, flags));
        }
    }

    closedir(directory);

    return true;
}
