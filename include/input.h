#ifndef INPUT_H
#define INPUT_H

// 3rd party lib
#include <GLFW/glfw3.h>

// Including string.h for memcpy operation
#include <string.h>

/*! @brief The function pointer type for a single keyboard key callback.
 *
 *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
 *  @param[in] mods Bit field describing which modifier keys (SHIFT, CONTROL etc) were
 *  held down. See more about these in the glfw documentation. 
 */
typedef void (* KeyAction)(GLFWwindow* window, int action, int mods);

/*! @brief  The KeyActionLib is a typedef for an array of KeyAction function pointers.

    The size of this array is equal to the last GLFW key code to allow for easy accessing of
    elements. For instance: to get the KeyAction associated with the keyboard letter E
*/
typedef KeyAction KeyActionLib[GLFW_KEY_LAST + 1];

// The current key action library that the callbacks will be fetched from
extern KeyActionLib current_key_action_lib;

/*! @brief Initializes the input library with a certain KeyActionLib.

    @param[in] window The window to fetch inputs from
    @param[in] key_action_lib The array of function pointers from individual key actions
*/
void input_initialize(GLFWwindow* window);

/*! @brief Copies the specified KeyActionLib over the current KeyActionLib.

    @param[in] new_key_action_lib The new KeyActionLib to copy over the old one
*/
void input_update_key_action_lib(KeyActionLib new_key_action_lib);

/*! @brief Updates the KeyAction associated with a single key

    @param[in] key The key to update the KeyAction of
    @param[in] new_key_action The new key action to be associated with this key
*/
void input_update_key_action(int key, KeyAction new_key_action);

#endif
