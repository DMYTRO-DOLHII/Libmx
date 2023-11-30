#include "uls.h"

int mx_validate_flags(t_flags *flags ) {
    int result = 0;

        if(flags->is_R) {
            result++;
        } else if (flags->is_R) {
            result--;
        } else if (flags->is_F) {
            result++;
        } else if (flags->is_p) {
            result++;
        } else if (flags->is_rev) {
            result--;
        } else if (flags->is_h) {
            result++;
        } else if (flags->is_e) {
            result++;
        } else if (flags->is_T) {
            result += 6;
        } else if (flags->is_at) {
            return 9;
        }

    result += 18;
    return result;
}




