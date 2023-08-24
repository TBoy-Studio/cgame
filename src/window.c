#include <window.h>

static unsigned char _isGlfwInitialized;
static unsigned char _isGladInitialized;
static Window _window;

static void framebufferSizeCallback(GLFWwindow* glfw_window, int width, int height)
{
    // Update the viewport
    glViewport(0, 0, width, height);

    // Update the window fields
    _window.width = width;
    _window.height = height;
}

unsigned char Window_build(const char* title)
{
    // If GLFW has not been initialized, try to do it now
    if(!_isGlfwInitialized && !glfwInit()) return 0; // If failed return 0    
    _isGlfwInitialized = 1; // glfw has been succesfully initialized

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

    // Make the window context the active context
    glfwMakeContextCurrent(glfw_window);

    // Set callback for when window changes size
    (void)glfwSetFramebufferSizeCallback(glfw_window, framebufferSizeCallback);

    // If GLAD has not been initialized, try to do it now
    if(!_isGladInitialized && !gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();    // abort if failed
        return 0;
    }
    _isGladInitialized = 1; // glad has been succesfully initialized

    // Configure OpenGL viewport
    glViewport(0, 0, width, height);

    // Fill in the window fields
    _window.win = glfw_window;
    _window.width = width;
    _window.height = height;

    return 1;
}

// TODO: MAKE SURE THIS NEVER NEEDS TO BE CALLED AND THEN REMOVE THE ENTIRE FUNCTION
Window* Window_getActiveWindow(void)
{
    return &_window; // eww
}

void Window_destroy(void)
{
    glfwDestroyWindow(_window.win);
    glfwTerminate();
    
    _isGlfwInitialized = 0;
    _isGladInitialized = 0;
    
    return;
}
