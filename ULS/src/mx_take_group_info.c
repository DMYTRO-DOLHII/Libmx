#include "uls.h"

char *mx_take_group_info(gid_t gid, bool number) {
    struct group *group = getgrgid(gid);

    if (group == NULL
        || number) {
        return mx_lltoa(gid);
    }

    return mx_strdup(group->gr_name);
}
