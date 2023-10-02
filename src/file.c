#include <file.h>

// The directory the executable is in
static char g_abs_path[FILENAME_MAX + 1];
static char *gp_exec_dir_append;
static unsigned short g_exec_dir_path_length;

void cgame_file_init(const char *executable_path)
{
    g_abs_path[FILENAME_MAX] = '\0';
    realpath(executable_path, g_abs_path);
    gp_exec_dir_append = strrchr(g_abs_path, '/') + 1;
    if(!gp_exec_dir_append) gp_exec_dir_append = strrchr(g_abs_path, '\\') + 1;
    g_exec_dir_path_length = gp_exec_dir_append - g_abs_path;
}

FILE *cgame_file_open(const char *file_path, const char *modes)
{
    strncpy(gp_exec_dir_append, file_path, FILENAME_MAX - g_exec_dir_path_length);
    return fopen(g_abs_path, modes);
}

