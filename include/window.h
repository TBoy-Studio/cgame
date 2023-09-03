#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

/*
    Function that gets called when the window size has changed
*/
typedef void (* Window_SizeChangedFunc)(int width, int height);

/*
    This struct holds some basic information about a window
*/
typedef struct{
    GLFWwindow* win;
    int width;
    int height;
    unsigned char success;
} Window;

/*
    Builds and starts showing a window in fullscreen mode
    on the user's primary monitor
*/
Window Window_createWindowFullscreen(const char *title);

/*
    Builds and starts showing a window in windowed mode
    on the user's primary monitor
*/
Window Window_createWindowWindowed(const char *title, int width, int height);

/*
    Set the function that gets called when the window size changes
*/
void Window_setSizeChangedAction(Window_SizeChangedFunc action);

/*
    Cleans up all resources from the window
*/
void Window_destroy(Window *window);

#endif
