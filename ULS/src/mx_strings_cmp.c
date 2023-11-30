#include "uls.h"

bool mx_strings_cmp(void *data1, void *data2) {
    return mx_strcmp(data1, data2) > 0;
}
