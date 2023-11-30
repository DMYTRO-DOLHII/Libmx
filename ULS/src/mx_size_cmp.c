#include "uls.h"

bool mx_size_cmp(void *data1, void *data2) {
    t_element *object_info1 = data1;
    t_element *object_info2 = data2;

    if (object_info1->stat.st_size == object_info2->stat.st_size) {
        return mx_strcmp(object_info1->name, object_info2->name) > 0;
    }

    return object_info1->stat.st_size < object_info2->stat.st_size;
}
