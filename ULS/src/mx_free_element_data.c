#include "uls.h"

void mx_free_element_data(t_element *element_data) {
    free(element_data->path);
    free(element_data->name);
    mx_strdel(&element_data->user);
    mx_strdel(&element_data->link);
    mx_strdel(&element_data->group);
    mx_del_strarr(&element_data->xattr_keys);
    acl_free(element_data->acl);
    free(element_data);
}
