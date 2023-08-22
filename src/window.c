#include <window.h>

unsigned char glfw_initialized = 0x00;
unsigned char glad_initialized = 0x00;
unsigned char amount_of_windows = 0;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

GLFWwindow* window_create(const char* title){
    // If GLFW has not been initialized, try to do it now
    if(!glfw_initialized && !glfwInit()) return NULL;
    glfw_initialized = 0x01;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    if(primary == NULL){
        glfwTerminate();
        return NULL;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    if(mode == NULL){
        glfwTerminate();
        return NULL;
    }

    unsigned int width = mode->width;
    unsigned int height = mode->height;

    GLFWwindow* window = glfwCreateWindow(width, height, title, primary, NULL);
    if(window == NULL){
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    (void)glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!glad_initialized && !gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();
        return NULL;
    }
    glad_initialized = 0x01;

    glViewport(0, 0, width, height);

    amount_of_windows++;
    return window;
}

void window_destroy(GLFWwindow *window){
    glfwDestroyWindow(window);
    amount_of_windows--;
    if(amount_of_windows == 0) glfwTerminate();
}
