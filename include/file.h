#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Initialize the file library.
    Needs to be called before any file operations.
*/
void cgame_file_init(const char *executable_path);

FILE *cgame_file_open(const char *file_path, const char *modes); 
