#include <libmx.h>
 
int mx_count_words(const char *str, char c) { 
    int i = 0;
    bool indifier = false;
    int words = 0;

    if (str) {
        while (str[i] == c) 
            i++;
        if (str[i]) 
            words++;
        while (str[i]) {
            if (str[i] == c) 
                indifier = true;
            else if (indifier) {
                    indifier = false;
                    words++;
                }
            i++;
        }
        return words;
    }
    return -1;
}
