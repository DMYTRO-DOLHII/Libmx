#include "uls.h"

t_element **mx_create_arr_from_list(t_list *objects_info, int *counter) {
    *counter = mx_list_size(objects_info);

    if (counter == 0) {
        return NULL;
    }

    t_element **array = malloc(sizeof(t_element *) * (*counter));

    for (int i = 0; i < *counter; i++) {
        array[i] = objects_info->data;
        objects_info = objects_info->next;
    }

    return array;
}
