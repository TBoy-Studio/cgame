#include <input.h>

KeyActionContext current_key_actions[GLFW_KEY_LAST + 1];
MouseButtonAction current_mouse_button_actions[GLFW_MOUSE_BUTTON_LAST + 1];
MouseScrollAction current_scroll_action;
MouseCursorAction current_cursor_action;

double input_mouse_cursor_last_x, input_mouse_cursor_last_y;
unsigned char first_mouse = 1;

void input_process(GLFWwindow* window){
    // Go through each key
    for(unsigned short i = 0; i <= GLFW_KEY_LAST; i++){
        KeyActionContext context = current_key_actions[i];
        if(context.last_key_action == GLFW_PRESS && context.repeat == GLFW_TRUE){
            // If it is currently being pressed and the repeat bool is set, execute the callback function
            context.action(window, GLFW_PRESS, current_key_actions[i].mods);
        }
    }
}

void input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // If key is unknown simply ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    KeyActionContext* context = &current_key_actions[(unsigned int)key];

    // If this key has an associated action and is not a repeat, execute it
    if(context->action != NULL && action != GLFW_REPEAT)
    {
        context->last_key_action = (unsigned char)action;
        context->mods = mods;
        context->action(window, action, mods);
    } 
}

void input_mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
    // If mouse button is unknown simply ignore
    if(button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;

    // If this mouse button has an associated action, execute it
    if(current_mouse_button_actions[(unsigned int)button] != NULL)
    {
        current_mouse_button_actions[(unsigned int)button](window, action, mods);
    }
}

void input_scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    // If there is a scroll action set, execute it
    if(current_scroll_action != NULL) current_scroll_action(window, xoffset, yoffset);
}

void input_cursor_callback(GLFWwindow* window, double xpos, double ypos){
    // Fix first mouse input
    if(first_mouse){
        input_mouse_cursor_last_x = xpos;
        input_mouse_cursor_last_y = ypos;
        first_mouse = 0;
    }

    // If there's a cursor action registered, execute it
    if(current_cursor_action != NULL) current_cursor_action(window, xpos, ypos);

    // Update the last coordinates with the most recent ones after all calculation is done
    input_mouse_cursor_last_x = xpos;
    input_mouse_cursor_last_y = ypos;
}

void input_initialize(GLFWwindow* window){
    // Set generic key callback
    glfwSetKeyCallback(window, input_key_callback);
    glfwSetMouseButtonCallback(window, input_mouse_button_callback);
    glfwSetScrollCallback(window, input_scroll_callback);
    glfwSetCursorPosCallback(window, input_cursor_callback);

    // Make sure to set all function pointers to zero
    // Prevents accidentally interpreting a random value as a function to execute
    memset(current_key_actions, 0x0, sizeof(KeyActionContext) * (GLFW_KEY_LAST + 1));
    memset(current_mouse_button_actions, 0x0, sizeof(MouseButtonAction) * (GLFW_MOUSE_BUTTON_LAST + 1));
    current_scroll_action = 0x0;
    current_cursor_action = 0x0;
}

void input_set_key_action_lib(KeyActionContext new_key_actions[GLFW_KEY_LAST + 1]){
    // Simply copy the new KeyActions over the old ones
    memcpy(current_key_actions, new_key_actions, sizeof(KeyActionContext) * (GLFW_KEY_LAST + 1));   
}

void input_set_key_action(int key, KeyAction new_key_action, unsigned char repeat){
    // If key outside range, ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    // Update function pointer
    current_key_actions[(unsigned int)key].action = new_key_action;
    current_key_actions[(unsigned int)key].repeat = repeat;
}

void input_set_mouse_button_action_lib(MouseButtonAction new_mouse_button_actions[GLFW_MOUSE_BUTTON_LAST + 1]){
    // Simply copy the new MouseButtonActions over the old ones
    memcpy(current_mouse_button_actions, new_mouse_button_actions, sizeof(MouseButtonAction) * (GLFW_MOUSE_BUTTON_LAST + 1));
}

void input_set_mouse_button_action(int button, MouseButtonAction new_mouse_button_action){
    // If key outside range, ignore
    if(button < 0 || button > GLFW_MOUSE_BUTTON_LAST) return;

    // Update function pointer
    current_mouse_button_actions[(unsigned int)button] = new_mouse_button_action;
}

void input_set_mouse_scroll_action(MouseScrollAction new_scroll_action){
    current_scroll_action = new_scroll_action;
}

void input_set_mouse_cursor_action(MouseCursorAction new_cursor_action){
    current_cursor_action = new_cursor_action;
}
