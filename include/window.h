#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

/*
    This struct holds some basic information about a window
*/
typedef struct{
    GLFWwindow* win;
    int width;
    int height;
} Window;

/*
    Builds and starts showing a window
*/
unsigned char Window_build(const char* title);

/*
    Returns a pointer to the window actively being rendered to.
    Function is gross, eww and yuck.
*/
Window* Window_getActiveWindow(void);

/*
    Cleans up all resources from the window
*/
void Window_destroy(void);

#endif
