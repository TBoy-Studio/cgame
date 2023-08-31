#include <input.h>

Input_KeyActionContext current_key_actions[GLFW_KEY_LAST + 1];
Input_MouseButtonActionFunc current_mouse_button_actions[GLFW_MOUSE_BUTTON_LAST + 1];
Input_MouseScrollActionFunc current_scroll_action;
Input_MouseCursorActionFunc current_cursor_action;

double mouse_last_x, mouse_last_y;
unsigned char first_mouse = 1;

static void _keyCallback
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

    Input_KeyActionContext* context = &current_key_actions[(unsigned int)key];

    // If this key has an associated action and is not a repeat, execute it
    if(context->action != NULL && action != GLFW_REPEAT)
    {
        context->last_key_action = (unsigned char)action;
        context->mods = mods;
        context->action(action, mods);
    } 
}

static void _mouseButtonCallback
(
    GLFWwindow* window, 
    int button, 
    int action, 
    int mods
)
{
    // If mouse button is unknown simply ignore
    if(button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;

    // If this mouse button has an associated action, execute it
    if(current_mouse_button_actions[(unsigned int)button] != NULL)
    {
        current_mouse_button_actions[(unsigned int)button](action, mods);
    }
}

static void _scrollCallback
(
    GLFWwindow* window, 
    double xoffset, 
    double yoffset
)
{
    // If there is a scroll action set, execute it
    if(current_scroll_action != NULL) current_scroll_action(yoffset);
}

static void _cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Fix first mouse input
    if(first_mouse){
        mouse_last_x = xpos;
        mouse_last_y = ypos;
        first_mouse = 0;
    }

    // If there's a cursor action registered, execute it
    if(current_cursor_action != NULL) current_cursor_action(xpos, ypos);

    // Update the last coordinates with the most recent ones 
    // after all calculation is done
    mouse_last_x = xpos;
    mouse_last_y = ypos;
}

void Input_init(Window *window)
{
    GLFWwindow* glfw_window = window->win;

    // Set generic key callback
    glfwSetKeyCallback(glfw_window, _keyCallback);
    glfwSetMouseButtonCallback(glfw_window, _mouseButtonCallback);
    glfwSetScrollCallback(glfw_window, _scrollCallback);
    glfwSetCursorPosCallback(glfw_window, _cursorCallback);

    // Make sure to set all function pointers to zero when initializing
    // Prevents accidentally interpreting a random value as a function to execute
    memset(
        current_key_actions, 
        0, 
        sizeof(Input_KeyActionContext) * (GLFW_KEY_LAST + 1)
    );
    memset(
        current_mouse_button_actions, 
        0, 
        sizeof(Input_MouseButtonActionFunc) * (GLFW_MOUSE_BUTTON_LAST + 1)
    );
    current_scroll_action = 0;
    current_cursor_action = 0;
}

void Input_setKeyActions
(
    Input_KeyActionContext key_actions[GLFW_KEY_LAST + 1]
)
{
    // Simply copy the new KeyActions over the old ones
    memcpy(
        current_key_actions, 
        key_actions, 
        sizeof(Input_KeyActionContext) * (GLFW_KEY_LAST + 1)
    );   
}

void Input_setKeyAction
(
    int key, 
    Input_KeyActionFunc new_key_action, 
    unsigned char repeat
)
{
    // If key outside range, ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    // Update function pointer
    current_key_actions[(unsigned int)key].action = new_key_action;
    current_key_actions[(unsigned int)key].repeat = repeat;
}

void Input_setMouseButtonActions(
    Input_MouseButtonActionFunc button_actions[GLFW_MOUSE_BUTTON_LAST + 1]
)
{
    // Simply copy the new MouseButtonActions over the old ones
    memcpy(
        current_mouse_button_actions, button_actions, 
        sizeof(Input_MouseButtonActionFunc) * (GLFW_MOUSE_BUTTON_LAST + 1)
    );
}

void Input_setMouseButtonAction
(
    int button, 
    Input_MouseButtonActionFunc button_action
)
{
    // If key outside range, ignore
    if(button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;

    // Update function pointer
    current_mouse_button_actions[(unsigned int)button] = button_action;
}

void Input_setMouseScrollAction(Input_MouseScrollActionFunc scroll_action)
{
    current_scroll_action = scroll_action;
}

void Input_setMouseCursorAction(Input_MouseCursorActionFunc cursor_action)
{
    current_cursor_action = cursor_action;
}

void Input_handleHoldDownKeys(void)
{
    // Go through each key
    for(unsigned short i = 0; i <= GLFW_KEY_LAST; i++)
    {
        Input_KeyActionContext *context = &current_key_actions[i];

        // If it is currently being pressed and the repeat bool is set,
        // execute the callback function
        if(context->last_key_action == GLFW_PRESS && context->repeat == GLFW_TRUE)
        {
            context->action(GLFW_PRESS, context->mods);
        }
    }
}

void Input_getPrevMouseCursorPosition(float result[2])
{
    result[0] = (float)mouse_last_x;
    result[1] = (float)mouse_last_y; 
}
