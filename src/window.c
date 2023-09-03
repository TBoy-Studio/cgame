#include <window.h>

static unsigned char _isGlfwInitialized;
static unsigned char _isGladInitialized;

static Window_SizeChangedFunc sizeChangedAction = 0;

static void framebufferSizeCallback(GLFWwindow* glfw_window, int width, int height)
{
    if(sizeChangedAction){
        sizeChangedAction(width, height);
    }
}

Window Window_createWindow(const char* title)
{
    Window window = {0, 0, 0, 0};

    // If a window has already been opened, don't build another one
    if(_isGlfwInitialized) return window;

    // If GLFW has not been initialized, try to do it now
    if(!_isGlfwInitialized && !glfwInit()) return window; // If failed return 0    
    _isGlfwInitialized = 1; // glfw has been succesfully initialized

    // Configure GLFW window for the OpenGL version that will run in it
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Get user's primary monitor
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    if(primary == NULL){
        glfwTerminate();
        return window;
    }

    // Get the videomode of that monitor
    const GLFWvidmode* mode = glfwGetVideoMode(primary);
    if(mode == NULL){
        glfwTerminate();
        return window;
    }

    // Get width and height from video mode
    int width = mode->width;
    int height = mode->height;

    // Call GLFW function to actually create the window
    GLFWwindow* glfw_window = glfwCreateWindow(1920, 1080, title, NULL, NULL);
    if(glfw_window == NULL){
        glfwTerminate();
        return window;
    }

    // Make the window context the active context
    glfwMakeContextCurrent(glfw_window);

    // Set callback for when window changes size
    (void)glfwSetFramebufferSizeCallback(glfw_window, framebufferSizeCallback);

    // If GLAD has not been initialized, try to do it now
    if(!_isGladInitialized && !gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();    // abort if failed
        return window;
    }
    _isGladInitialized = 1; // glad has been succesfully initialized

    // Configure OpenGL viewport
    glViewport(0, 0, width, height);

    // Fill in the window fields
    window.win = glfw_window;
    window.width = width;
    window.height = height;
    window.success = 1;

    return window;
}

void Window_setSizeChangedAction(Window_SizeChangedFunc action)
{
    sizeChangedAction = action;
}

void Window_destroy(Window *window)
{
    glfwDestroyWindow(window->win);
    glfwTerminate();
    
    _isGlfwInitialized = 0;
    _isGladInitialized = 0;
    
    return;
}
