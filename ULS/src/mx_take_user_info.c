#include "uls.h"

char *mx_take_user_info(uid_t uid, bool number) {
    struct passwd *passwd = getpwuid(uid);

    if (passwd == NULL
        || number) {
        return mx_lltoa(uid);
    }

    return mx_strdup(passwd->pw_name);
}
