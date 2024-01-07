#include <file.h>

static char * executable_directory = NULL;
static char * full_path = NULL;

// Function to get the directory of the executable
char* _get_executable_dir() {
#ifdef _WIN32
    char* buffer;
    size_t size = MAX_PATH;
    buffer = (char*)malloc((size + 1) * sizeof(char));

    DWORD length = GetModuleFileName(NULL, buffer, size);
    if (length == 0) {
        free(buffer);
        return NULL;
    }

    // Remove the executable name to get the directory
    _splitpath(buffer, NULL, buffer, NULL, NULL);

    return buffer;
#else
    char* buffer;
    size_t size = PATH_MAX;
    buffer = (char*)malloc((size + 1) * sizeof(char));

    ssize_t length = readlink("/proc/self/exe", buffer, size);
    if (length == -1) {
        free(buffer);
        return NULL;
    }

    // Remove the executable name to get the directory
    dirname(buffer);

    return buffer;
#endif
}

// Function to construct the full path
void _construct_full_path(const char* relative_path) {
    size_t len = strlen(executable_directory) + strlen(relative_path) + 2;

    // Construct the full path
#ifdef _WIN32
    snprintf(full_path, len, "%s\\%s", executable_directory, relative_path);
#else
    snprintf(full_path, len, "%s/%s", executable_directory, relative_path);
#endif
}

void cgame_file_init()
{
    executable_directory = _get_executable_dir();
    full_path = (char *)malloc(PATH_MAX);

    if(executable_directory == NULL || full_path == NULL)
    {
        // Ai caramba
        fprintf(stderr, "Failed to initialize file system!");
    }
}

/*
    Constructs the absolute path from the specified relative path
    and the current working directory (where the executable is)
    and opens the file at that path
*/
FILE * cgame_file_open(const char * relative_path, const char * modes)
{
    _construct_full_path(relative_path);
    return fopen(full_path, modes);
}

void cgame_file_clean()
{
    free(executable_directory);
    free(full_path);
}