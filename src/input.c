#include <input.h>

KeyActionLib current_key_action_lib;

void input_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key < 0) return;                                             // If key is unknown simply ignore
    if(current_key_action_lib[(unsigned int)key] != NULL)
    {
        current_key_action_lib[(unsigned int)key](window, action, mods);    // If this key has an associated action, execute it
    } 
}

void input_initialize(GLFWwindow* window){
    glfwSetKeyCallback(window, input_key_callback); // Set generic key callback
}

void input_update_key_action_lib(KeyActionLib new_key_action_lib){
    memcpy(current_key_action_lib, new_key_action_lib, sizeof(KeyActionLib));   // Simply copy the new KeyActionLib over the old one
}

void input_update_key_action(int key, KeyAction new_key_action){
    if(key < 0 || key > GLFW_KEY_LAST) return;                  // If key outside range, ignore
    current_key_action_lib[(unsigned int)key] = new_key_action; // Update function pointer
}
