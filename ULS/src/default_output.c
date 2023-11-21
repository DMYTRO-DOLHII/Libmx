#include "../inc/uls.h"

void default_colorful_output(void) {
    DIR *dir = opendir(".");
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            char full_path[100];
            snprintf(full_path, sizeof(full_path), "%s/%s", ".", entry->d_name);

            struct stat statbuf;
            if (stat(full_path, &statbuf) == -1) {
                perror("stat");
                continue;
            }

            print_unit_color(entry->d_name, statbuf.st_mode);
        }
    }

    closedir(dir);
}

void default_output(void) {
    DIR *dir = opendir(".");

    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        print_unit(entry->d_name, DEFAULT_COLOR);
    }
}
