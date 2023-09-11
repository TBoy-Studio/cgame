#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

/*
    Function that gets called when the window size has changed
*/
typedef void (* CGameWindowSizeChangedFunc)(int width, int height);

/*
    This struct holds some basic information about a window
*/
typedef struct{
    GLFWwindow* win;
    int width;
    int height;
    unsigned char success;
} CGameWindow;

/*
    Builds and starts showing a window in fullscreen mode
    on the user's primary monitor
*/
CGameWindow cgame_window_create_fullscreen(const char *title);

/*
    Builds and starts showing a window in windowed mode
    on the user's primary monitor
*/
CGameWindow cgame_window_create_windowed(const char *title, int width, int height);

/*
    Set the function that gets called when the window size changes
*/
void cgame_window_set_size_changed_action(CGameWindowSizeChangedFunc action);

/*
    Cleans up all resources from the window
*/
void cgame_window_destroy(CGameWindow *window);
