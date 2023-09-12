#include <input.h>

static CGameInputKeyActionContext g_current_key_actions[GLFW_KEY_LAST + 1];
static CGameInputMouseButtonActionFunc g_current_mouse_button_actions[GLFW_MOUSE_BUTTON_LAST + 1];
static CGameInputMouseScrollActionFunc g_current_scroll_action;
static CGameInputMouseCursorActionFunc g_current_cursor_action;

double g_mouse_last_x, g_mouse_last_y;
unsigned char g_first_mouse = 1;

static void _key_callback
(
    GLFWwindow* window, 
    int key, 
    int scancode, 
    int action, 
    int mods
)
{
    // If key is unknown simply ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    CGameInputKeyActionContext* context = &g_current_key_actions[(unsigned int)key];

    // If this key has an associated action and is not a repeat, execute it
    if(context->action != NULL && action != GLFW_REPEAT)
    {
        context->last_key_action = (unsigned char)action;
        context->mods = mods;
        context->action(action, mods);
    } 
}

static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // If mouse button is unknown simply ignore
    if(button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;

    // If this mouse button has an associated action, execute it
    if(g_current_mouse_button_actions[(unsigned int)button] != NULL)
    {
        g_current_mouse_button_actions[(unsigned int)button](action, mods);
    }
}

static void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // If there is a scroll action set, execute it
    if(g_current_scroll_action != NULL) g_current_scroll_action(yoffset);
}

static void _cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
    // Fix first mouse input
    if(g_first_mouse){
        g_mouse_last_x = xpos;
        g_mouse_last_y = ypos;
        g_first_mouse = 0;
    }

    // If there's a cursor action registered, execute it
    if(g_current_cursor_action != NULL) g_current_cursor_action(xpos, ypos);

    // Update the last coordinates with the most recent ones 
    // after all calculation is done
    g_mouse_last_x = xpos;
    g_mouse_last_y = ypos;
}

void cgame_input_init()
{
    // Make sure to set all function pointers to zero when initializing
    // Prevents accidentally interpreting a random value as a function to execute
    memset(
        g_current_key_actions, 
        0, 
        sizeof(CGameInputKeyActionContext) * (GLFW_KEY_LAST + 1)
    );
    memset(
        g_current_mouse_button_actions, 
        0, 
        sizeof(CGameInputMouseButtonActionFunc) * (GLFW_MOUSE_BUTTON_LAST + 1)
    );
    g_current_scroll_action = 0;
    g_current_cursor_action = 0;
}

void cgame_input_register_on_window(CGameWindow *window)
{
    GLFWwindow* glfw_window = window->win;

    // Set generic key callback
    glfwSetKeyCallback(glfw_window, _key_callback);
    glfwSetMouseButtonCallback(glfw_window, _mouse_button_callback);
    glfwSetScrollCallback(glfw_window, _scroll_callback);
    glfwSetCursorPosCallback(glfw_window, _cursor_callback);
}

void cgame_input_set_key_actions(CGameInputKeyActionContext key_actions[GLFW_KEY_LAST + 1])
{
    // Simply copy the new KeyActions over the old ones
    memcpy(
        g_current_key_actions, 
        key_actions, 
        sizeof(CGameInputKeyActionContext) * (GLFW_KEY_LAST + 1)
    );   
}

void cgame_input_set_key_action(int key, CGameInputKeyActionFunc key_action, unsigned char repeat)
{
    // If key outside range, ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    // Update function pointer
    g_current_key_actions[(unsigned int)key].action = key_action;
    g_current_key_actions[(unsigned int)key].repeat = repeat;
}

void cgame_input_set_mouse_button_actions(CGameInputMouseButtonActionFunc button_actions[GLFW_MOUSE_BUTTON_LAST + 1])
{
    // Simply copy the new MouseButtonActions over the old ones
    memcpy(
        g_current_mouse_button_actions, button_actions, 
        sizeof(CGameInputMouseButtonActionFunc) * (GLFW_MOUSE_BUTTON_LAST + 1)
    );
}

void cgame_input_set_mouse_button_action(int button, CGameInputMouseButtonActionFunc button_action)
{
    // If key outside range, ignore
    if(button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;

    // Update function pointer
    g_current_mouse_button_actions[(unsigned int)button] = button_action;
}

void cgame_input_set_scroll_action(CGameInputMouseScrollActionFunc scroll_action)
{
    g_current_scroll_action = scroll_action;
}

void cgame_input_set_cursor_action(CGameInputMouseCursorActionFunc cursor_action)
{
    g_current_cursor_action = cursor_action;
}

void cgame_input_handle_hold_down_keys(void)
{
    // Go through each key
    for(unsigned short i = 0; i <= GLFW_KEY_LAST; i++)
    {
        CGameInputKeyActionContext *context = &g_current_key_actions[i];

        // If it is currently being pressed and the repeat bool is set,
        // execute the callback function
        if(context->last_key_action == GLFW_PRESS && context->repeat == GLFW_TRUE)
        {
            context->action(GLFW_PRESS, context->mods);
        }
    }
}

void cgame_input_get_previous_cursor_position(float result[2])
{
    result[0] = (float)g_mouse_last_x;
    result[1] = (float)g_mouse_last_y; 
}
