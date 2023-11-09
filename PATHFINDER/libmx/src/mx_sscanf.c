#include <libmx.h>

int mx_sscanf(const char *str, const char *format, char *start, char *end, int *weight) {
   int parsed_values = 0;

    if (start) {
        *start = '\0';
    }
    if (end) {
        *end = '\0';
    }

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                int i = 0;
                char *city = (parsed_values == 0 && start) ? start : end;
                while (*str != '\0' && *str != ' ' && *str != ',' && *str != '-') {
                    if (city) {
                        city[i] = *str;
                    }
                    i++;
                    str++;
                }
                if (city) {
                    city[i] = '\0';
                }
                parsed_values++;
            } else if (*format == 'd') {
                *weight = 0;
                while (*str >= '0' && *str <= '9') {
                    *weight = *weight * 10 + (*str - '0');
                    str++;
                }
                parsed_values++;
            }
        } else {
            if (*str != *format) {
                return parsed_values;
            }
            str++;
        }
        format++;
    }

    return parsed_values;
}