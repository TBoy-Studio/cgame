#include <window.h>

unsigned char glfw_initialized = 0;
unsigned char glad_initialized = 0;
int gl_version = 0;

Window window;

void framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height){
    glViewport(0, 0, width, height);

    window.width = width;
    window.height = height;
}

unsigned char window_create(const char* title){
    // If GLFW has not been initialized, try to do it now
    if(!glfw_initialized && !glfwInit()) return 0; // If failed return 0
    
    glfw_initialized = 1; // glfw has been succesfully initialized

    // Configure GLFW window for the OpenGL version that will run in it
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Get user's primary monitor
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    if(primary == NULL){
        glfwTerminate();
        return 0;
    }

    // Get the videomode of that monitor
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    if(mode == NULL){
        glfwTerminate();
        return 0;
    }

    // Get width and height from video mode
    int width = mode->width;
    int height = mode->height;

    // Call GLFW function to actually create the window
    GLFWwindow* glfw_window = glfwCreateWindow(width, height, title, primary, NULL);
    if(glfw_window == NULL){
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(glfw_window);

    (void)glfwSetFramebufferSizeCallback(glfw_window, framebuffer_size_callback);

    // If GLAD has not been initialized, try to do it now
    if(!glad_initialized && !gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();    // abort if failed
        return 0;
    }
    glad_initialized = 1; // glad has been succesfully initialized

    glViewport(0, 0, width, height);

    window.win = glfw_window;
    window.width = width;
    window.height = height;

    return 1;
}

void window_destroy(void){
    glfwDestroyWindow(window.win);
    glfwTerminate();
    
    glfw_initialized = 0;
    glad_initialized = 0;
    
    return;
}
