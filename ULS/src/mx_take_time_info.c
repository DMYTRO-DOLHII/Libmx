#include "uls.h"

struct timespec mx_take_time_info(struct stat *stat, t_time time_type) {
    if (time_type == MOD) {
        return stat->st_mtimespec;
    } else if (time_type == STAT) {
        return stat->st_ctimespec;
    } else if (time_type == ACC) {
        return stat->st_atimespec;
    } else if (time_type == CREATE) {
        return stat->st_birthtimespec;
    }
    return stat->st_mtimespec;
}
