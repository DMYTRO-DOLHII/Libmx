#include "uls.h"

int mx_maxlen_default(t_list *elements_data) {
    int width = 0;

    while (elements_data != NULL) {
        t_element *object_info = elements_data->data;
        int len = mx_strlen(object_info->name);

        if (width < len) {
            width = len;
        }

        elements_data = elements_data->next;
    }

    return width;
}
