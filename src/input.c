#include <input.h>

KeyAction current_key_actions[GLFW_KEY_LAST + 1];
MouseButtonAction current_mouse_button_actions[GLFW_MOUSE_BUTTON_LAST + 1];
MouseScrollAction current_scroll_action;

void input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    // If key is unknown simply ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    // If this key has an associated action, execute it
    if(current_key_actions[(unsigned int)key] != NULL)
    {
        current_key_actions[(unsigned int)key](window, action, mods);
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

void input_initialize(GLFWwindow* window){
    // Set generic key callback
    glfwSetKeyCallback(window, input_key_callback);
    glfwSetMouseButtonCallback(window, input_mouse_button_callback);
    glfwSetScrollCallback(window, input_scroll_callback);

    // Make sure to set all function pointers to zero
    // Prevents accidentally interpreting a random value as a function to execute
    memset(current_key_actions, 0x0, sizeof(KeyAction) * (GLFW_KEY_LAST + 1));
    memset(current_mouse_button_actions, 0x0, sizeof(MouseButtonAction) * (GLFW_MOUSE_BUTTON_LAST + 1));
    current_scroll_action = 0x0;
}

void input_set_key_action_lib(KeyAction new_key_actions[GLFW_KEY_LAST + 1]){
    // Simply copy the new KeyActions over the old ones
    memcpy(current_key_actions, new_key_actions, sizeof(KeyAction) * (GLFW_KEY_LAST + 1));   
}

void input_set_key_action(int key, KeyAction new_key_action){
    // If key outside range, ignore
    if(key < 0 || key > GLFW_KEY_LAST) return;

    // Update function pointer
    current_key_actions[(unsigned int)key] = new_key_action;
}

void input_set_mouse_button_action_lib(MouseButtonActionLib new_mouse_button_actions){
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
