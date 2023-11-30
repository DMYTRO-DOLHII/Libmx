#include "uls.h"

bool mx_time_cmp(void *data1, void *data2) {
    t_element *element_data1 = data1;
    t_element *element_data2 = data2;

    if (element_data1->timespec.tv_sec == element_data2->timespec.tv_sec) {
        if (element_data1->timespec.tv_nsec == element_data2->timespec.tv_nsec) {
            return mx_strcmp(element_data1->name, element_data2->name) > 0;
        }

        return element_data1->timespec.tv_nsec < element_data2->timespec.tv_nsec;
    }

    return element_data1->timespec.tv_sec < element_data2->timespec.tv_sec;
}
