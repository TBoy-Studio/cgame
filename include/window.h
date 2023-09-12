#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>

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
    vec4 background_color;
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
    Set the background color of this window
*/
void cgame_window_set_background_color(CGameWindow *window, vec4 *color);

/*
    Used by cgame to draw the background color,
    non library code should never have to interract with this function
*/
void cgame_window_draw_background(CGameWindow *window);

/*
    Cleans up all resources from the window
*/
void cgame_window_destroy(CGameWindow *window);
