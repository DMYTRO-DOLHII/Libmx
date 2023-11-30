#ifndef ULS_H
#define ULS_H

#include <dirent.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <unistd.h>
#include "libmx.h"

/* uls configuration pack */
typedef enum {
    ONECOL_OUTPUT,    // -1
    DEFAULT_OUTPUT,     // -C
    ONEROW_OUTPUT,          // -m
    L_OUTPUT,            // -l
} t_output;

typedef enum {
    MOD,      // default
    STAT,     // -c
    ACC,            // -u
    CREATE,          // -U
} t_time;

typedef enum {
    NAME,           // default
    TIME,           // -t
    SIZE,           // -S
    NONE,              // -f
} t_sort;

typedef enum {
    HIDDEN,          // default
    DOTS,            // -A
    ZERO,            // -a
} t_hidden;

typedef struct {
    t_output format;
    t_time time_type;
    t_sort sort_type;
    t_hidden ommit;
    bool is_R;                 // -R
    bool is_G;                  // -G
    bool is_F;                  // -F
    bool is_p;                     // -p
    bool is_rev;              // -r
    bool is_h;            // -h
    bool is_e;       // -e
    bool is_T;        // -T
    bool is_at;   // -@
    bool is_g;                // -g
    bool is_o;                // -o
    bool is_x;               // -x
    bool is_n;       // -n
    bool is_q;       // -q
    bool is_H;            // -H
} t_flags;

t_flags *mx_make_flags(void);
t_flags *mx_init_flags(int argc, char *argv[]);

/* Objects (files and directories) information pack */
typedef struct {
    char *path;
    char *name;
    char *user;
    char *link;
    char *group;
    char **xattr_keys;
    acl_t acl;
    struct stat stat;
    struct timespec timespec;
} t_element;

char *mx_take_user_info(uid_t uid, bool number);
char *mx_take_group_info(gid_t gid, bool number);
struct timespec mx_take_time_info(struct stat *stat, t_time time_type);
char **mx_take_xtr_info(const char *filename);
t_element *mx_init_element_data(const char *directory, const char *name, t_flags *config);
bool mx_is_hidden(const char *name, t_hidden ignore_type);
bool mx_take_dir_info(t_list **objects, const char *name, t_flags *config);
void mx_free_element_data(t_element *element_data);
blkcnt_t mx_block_num(t_list *elements);

/* File information sorting pack */
bool mx_strings_cmp(void *data1, void *data2);
void mx_arrange_elements(t_list *objects_names, t_sort sort_type);
bool mx_name_cmp(void *data1, void *data2);
bool mx_time_cmp(void *data1, void *data2);
bool mx_size_cmp(void *data1, void *data2);
void mx_sort_by_parameters(t_list *elements_data, t_sort sort_type, bool reverse);

/* Outputs packages */
typedef struct {
    int links;
    int user;
    int group;
    int size;
} t_width;

/* Formatted output pack */
void mx_element_color_output(mode_t mode);
int mx_element_class_output(mode_t mode, bool slash_only);
char *mx_change_unprintable(const char *name);
void mx_element_name_output(const char *name, bool replace_non_graphic);
int mx_element_inf_output(t_element *element_data, t_flags *config);
void mx_onecol_output(t_list *elements_data, t_flags *config);
void mx_onerow_output(t_list *elements_data, t_flags *config);
void mx_output_type(t_list *elements_data, t_flags *config);

/* Long formatted output pack */
void mx_element_type_output(mode_t mode);
void mx_element_perm_output(mode_t mode);
void mx_print_l_str(char *string, int width, bool align_right);
void mx_lnum_out(long long number, int width);
void mx_element_time_output(time_t ptime, bool full);
double mx_long_round(double number);
void mx_element_size_output(off_t size, int width);
void mx_element_xtr_output(t_element *element_data, bool human_readable);
void mx_element_acl_ouyput(acl_t acl);
void mx_L_output_single(t_element *elements_data, t_width *width, t_flags *config);
t_width mx_maxlen_l(t_list *elements_data, t_flags *config);
void mx_L_output(t_list *elements_data, t_flags *config);

/* Multicolumn formatted output pack */
int mx_maxlen_default(t_list *elements_data);
int mx_find_space_len(void);
void mx_cols_output(int width, int tab_width);
t_element **mx_create_arr_from_list(t_list *elements_data, int *count);
void mx_default_output(t_list *elements_data, t_flags *config);

/* uls main pack */
t_list *mx_take_elements(int argc, char *argv[]);
void mx_error_output(const char *file);
void mx_free_elements(t_list *elements_data);
void mx_output_files(t_list *files, t_flags *config);
bool mx_output_directory(t_element *element_data, t_flags *config, bool print_object_name);
bool mx_output_directories(t_list *directories, t_flags *config, bool print_objects_names);
int mx_output_elements(t_list *elements, t_flags *config);


char *mx_lltoa(long long number);
t_list *mx_sort_list_objects(t_list *list, bool (*cmp)(void *, void *), bool reverse);
char *mx_strjoin_with_delim(const char *s1, const char *s2, char delim);
int mx_validate_elements(t_list* elements);
int mx_validate_flags(t_flags *flags);



#endif

