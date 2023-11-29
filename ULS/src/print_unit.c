#include "../inc/uls.h"

void print_unit(const char *unit, char *color) {
    mx_printstr(color);
    mx_printstr(unit);
    mx_printstr(RESET_COLOR);
    mx_printstr("  ");
}

void print_unit_info(Unit *unit, Max_Size *max_size, Flag *flag) {
    if(flag->i) {
        // mx_printstr(mx_utoa(unit->inode));
        printstr_formatted(mx_utoa(unit->inode), 8, true);
        mx_printchar(' ');
    }
    mx_printchar(unit->type);
    mx_printstr(unit->permissions);
    mx_printchar(' ');

    if (unit->nlinks) {
        printint_formatted(unit->nlinks, max_size->nlinks);
    }
    else {
        mx_printstr("  ");
    }

    if (!flag->g) {
        mx_printchar(' ');
        printstr_formatted(mx_char_to_str(unit->owner), max_size->username, true);
    }
    else
        mx_printchar(' ');
    if (!flag->g && !flag->o)
        mx_printstr("  ");
    if (!flag->o) {
        printstr_formatted(mx_char_to_str(unit->group), max_size->groupname, true);
    }
    if (flag->h) {
        mx_printstr("   ");
        if (max_size->h_size == 2)
            mx_printstr("  ");
        printstr_formatted(mx_char_to_str(unit->h_size), max_size->h_size, true);
    }
    else {
        (unit->size == 0) ? mx_printstr(" ") : mx_printstr("  ");
        printint_formatted(unit->size, max_size->size);
    }

    mx_printchar(' ');
    mx_printstr(unit->date_time);
    mx_printchar(' ');
    if(flag->G) {
        struct stat sb;
        if (lstat(unit->name, &sb) == -1) {
            perror("Cannot get file information");
        }   
        switch_strcolor(sb);
    }

    mx_printstr(unit->name);
    if(flag->G) mx_printstr(DEFAULT_COLOR);
    if(flag->p && is_dir(unit->name)) mx_printchar('/');
    else if(flag->F && is_executable(unit->name)) {
        mx_printchar('*');
    }
    else if(flag->F && is_link(unit->name)) {
        mx_printchar('@');
    }
    else if(flag->F && is_socket(unit->name)) {
        mx_printchar('=');
    }
    else if(flag->F && is_whiteout(unit->name)) {
        mx_printchar('%');
    }
    else if(flag->F && is_fifo(unit->name)) {
        mx_printchar('|');
    }

    if (unit->type == 'l') {
        mx_printstr(" -> ");
        mx_printstr(unit->symlink);
    }
    mx_printchar('\n');
    if(flag->at && unit->xattr_keys != NULL) {
        print_xattr(&unit->xattr_keys, flag);
    }
}

void print_long_list(Directory *current, Flag *flag) {
    int total_blocks = 0;
    struct stat sb;
    if (lstat(current->name, &sb) == -1) {
        perror("Cannot get directory information");
        exit(1);
    }
    if (!S_ISLNK(sb.st_mode) || current->name[mx_strlen(current->name) - 1] == '/') {
        mx_printstr("total ");

        for (int i = 0; i < current->units_count; ++i) {
            if (lstat(current->units[i].name, &sb) == -1) {
                perror("Cannot get file information");
                continue;
            }
            total_blocks += (int)(sb.st_blocks);
        }
        mx_printint(total_blocks);
        mx_printchar('\n');
    }

    Max_Size max_size = {
        .nlinks = 0, 
        .username = 0, 
        .groupname = 0, 
        .size = 0, 
        .h_size = 0
    };


    for (int i = 0; i < current->units_count; ++i) {
        int group_len = mx_strlen(current->units[i].group);
        int nlinks_len = mx_intlen(current->units[i].nlinks);
        int size_len = mx_intlen(current->units[i].size);
        int name_len = mx_strlen(current->units[i].group);
        int h_size_len = mx_strlen(current->units[i].h_size);

        if (group_len > max_size.groupname) {
            max_size.groupname = group_len;
        }
        if (nlinks_len > max_size.nlinks) {
            max_size.nlinks = nlinks_len;
        }
        if (flag->h) {
            if (h_size_len > max_size.h_size) {
                max_size.h_size = h_size_len;
            }
        }
        else {
            if (size_len > max_size.size) {
                max_size.size = size_len;
            }
        }
        if (name_len > max_size.username) {
            max_size.username = name_len;
        }
    }

    for (int i = 0; i < current->units_count; ++i) {
        print_file_entry(current->units, i, max_size, flag);
        if(acl_get_file(current->units[i].name, ACL_TYPE_EXTENDED) && flag->e) {
                char **str_split = mx_strsplit(acl_to_text(acl_get_file(current->units[i].name, ACL_TYPE_EXTENDED), NULL), '\n');
                for (int i = 1; str_split[i] != NULL; i++) {
                    char **parts = mx_strsplit(str_split[i], ':');
                    mx_printchar(' ');
                    mx_printint(i - 1);
                    mx_printstr(": ");
                    mx_printstr(parts[0]);
                    mx_printchar(':');
                    mx_printstr(parts[2]);
                    mx_printchar(' ');
                    mx_printstr(parts[4]);
                    mx_printchar(' ');
                    mx_printstr(parts[5]);
                    mx_printchar('\n');
                    mx_del_strarr(&parts);
                }
                mx_del_strarr(&str_split);
        }
    }
}
