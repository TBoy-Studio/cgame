#include <window.h>

#define WINDOW_ZERO_INIT {0, 0, 0, 0};

static unsigned char g_is_glfw_initialized;
static unsigned char g_is_glad_initialized;

static CGameWindowSizeChangedFunc sizeChangedAction = 0;

static void _framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height)
{
    if(sizeChangedAction){
        sizeChangedAction(width, height);
    }
}

CGameWindow cgame_window_create_fullscreen(const char *title)
{
    CGameWindow window = WINDOW_ZERO_INIT;

    // If a window has already been opened, don't build another one
    if(g_is_glfw_initialized) return window;

    // If GLFW has not been initialized, try to do it now
    if(!g_is_glfw_initialized && !glfwInit()) return window; // If failed return 0    
    g_is_glfw_initialized = 1; // glfw has been succesfully initialized

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
    GLFWwindow* glfw_window = glfwCreateWindow(width, height, title, primary, NULL);
    if(glfw_window == NULL){
        glfwTerminate();
        return window;
    }

    // Make the window context the active context
    glfwMakeContextCurrent(glfw_window);

    // Set callback for when window changes size
    (void)glfwSetFramebufferSizeCallback(glfw_window, _framebuffer_size_callback);

    // If GLAD has not been initialized, try to do it now
    if(!g_is_glad_initialized && !gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();    // abort if failed
        return window;
    }
    g_is_glad_initialized = 1; // glad has been succesfully initialized

    // Configure OpenGL viewport
    glViewport(0, 0, width, height);

    // Fill in the window fields
    window.win = glfw_window;
    window.width = width;
    window.height = height;
    window.success = 1;

    return window;
}

CGameWindow cgame_window_create_windowed(const char *title, int width, int height)
{
    CGameWindow window = WINDOW_ZERO_INIT;

    // If a window has already been opened, don't build another one
    if(g_is_glfw_initialized) return window;

    // If GLFW has not been initialized, try to do it now
    if(!g_is_glfw_initialized && !glfwInit()) return window; // If failed return 0    
    g_is_glfw_initialized = 1; // glfw has been succesfully initialized

    // Configure GLFW window for the OpenGL version that will run in it
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Call GLFW function to actually create the window
    GLFWwindow* glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if(glfw_window == NULL){
        glfwTerminate();
        return window;
    }

    // Make the window context the active context
    glfwMakeContextCurrent(glfw_window);

    // Set callback for when window changes size
    (void)glfwSetFramebufferSizeCallback(glfw_window, _framebuffer_size_callback);

    // If GLAD has not been initialized, try to do it now
    if(!g_is_glad_initialized && !gladLoadGL(glfwGetProcAddress)){
        glfwTerminate();    // abort if failed
        return window;
    }
    g_is_glad_initialized = 1; // glad has been succesfully initialized

    // Configure OpenGL viewport
    glViewport(0, 0, width, height);

    // Fill in the window fields
    window.win = glfw_window;
    window.width = width;
    window.height = height;
    window.success = 1;

    return window;
}

void cgame_window_set_size_changed_action(CGameWindowSizeChangedFunc action)
{
    sizeChangedAction = action;
}

void cgame_window_destroy(CGameWindow *window)
{
    glfwDestroyWindow(window->win);
    glfwTerminate();
    
    g_is_glfw_initialized = 0;
    g_is_glad_initialized = 0;
    
    return;
}
