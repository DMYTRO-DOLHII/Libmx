#include "uls.h"

bool mx_name_cmp(void *data1, void *data2) {
    t_element *element_data1 = data1;
    t_element *element_data2 = data2;

    return mx_strcmp(element_data1->name, element_data2->name) > 0;
}
