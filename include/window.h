#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define MAX_NUM_WINDOWS 8

typedef struct{
    GLFWwindow* win;
    int width;
    int height;
} Window;

extern Window window;

unsigned char window_create(const char* title);
void window_destroy(void);

#endif
