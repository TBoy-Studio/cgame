#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <libgen.h>
#include <limits.h>
#endif

/*
    Initialize the file system. Only used internally by cgame to save
    the executable directory for handling relative file paths
*/
void cgame_file_init();

/*
    Constructs the absolute path from the specified relative path
    and the executable directory and opens the file at that path
*/
FILE * cgame_file_open(const char * relative_path, const char * modes);

/*
    Cleans up the file system. Only used internally by cgame to clear resources.
*/
void cgame_file_clean();