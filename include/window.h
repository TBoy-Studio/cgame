#ifndef WINDOW_H
#define WINDOW_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

GLFWwindow* window_create(const char* title);
void window_destroy(GLFWwindow *window);

#endif
