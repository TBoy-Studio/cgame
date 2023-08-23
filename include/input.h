#ifndef INPUT_H
#define INPUT_H

// 3rd party lib
#include <GLFW/glfw3.h>

// Including string.h for memcpy operation
#include <string.h>

/*! @brief The function pointer type for a single keyboard key callback.
 *
 *  @param[in] window The window the event occured in
 *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
 *  @param[in] mods Bit field describing which modifier keys (SHIFT, CONTROL etc) were
 *  held down. See more about these in the glfw documentation. 
 */
typedef void (* KeyAction)(GLFWwindow* window, int action, int mods);

/*! @brief The function pointer type for a single mouse button callback.
 *
 *  @param[in] window The window the event occured in
 *  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.
 *  @param[in] mods Bit field describing which modifier keys (SHIFT, CONTROL etc) were
 *  held down. See more about these in the glfw documentation. 
 */
typedef void (* MouseButtonAction)(GLFWwindow* window, int action, int mods);

/*! @brief The function pointer type for a single mouse scroll callback
 *
 *  @param[in] window The window the event occured in
 *  @param[in] xoffset The x-offset of the scroll (can be usually be ignored as scroll happens along y axis)
 *  @param[in] yoffset The y-offset of the scroll (The amount the user has scrolled)
*/
typedef void (* MouseScrollAction)(GLFWwindow* window, double xoffset, double yoffset);

/*! @brief  The KeyActionLib is a typedef for an array of KeyAction function pointers.

    The size of this array is equal to the last GLFW key code to allow for easy accessing of
    elements
*/
typedef KeyAction KeyActionLib[GLFW_KEY_LAST + 1];

/*! @brief  The MouseButtonActionLib is a typedef for an array of MouseButtonAction function pointers.

    The size of this array is equal to the last GLFW mouse button code to allow for easy accessing of
    elements
*/
typedef MouseButtonAction MouseButtonActionLib[GLFW_MOUSE_BUTTON_LAST + 1];

/*! @brief Initializes the input library.

    @param[in] window The window to fetch inputs from
*/
void input_initialize(GLFWwindow* window);

/*! @brief Copies the specified KeyActionLib over the current KeyActionLib.

    @param[in] new_key_action_lib The new KeyActionLib to copy over the old one
*/
void input_set_key_action_lib(KeyActionLib new_key_action_lib);

/*! @brief Updates the KeyAction associated with a single key

    @param[in] key The key to update the KeyAction of
    @param[in] new_key_action The new key action to be associated with this key
*/
void input_set_key_action(int key, KeyAction new_key_action);

/*! @brief Copies the specified MouseButtonActionLib over the current MouseButtonActionLib.

    @param[in] new_mouse_button_action_lib The new KeyActionLib to copy over the old one
*/
void input_set_mouse_button_action_lib(MouseButtonActionLib new_mouse_button_action_lib);

/*! @brief Updates the MouseButtonAction associated with a single mouse button

    @param[in] key The mouse button to update the MouseButtonAction of
    @param[in] new_key_action The new action to be associated with this mouse button
*/
void input_set_mouse_button_action(int button, MouseButtonAction new_key_action);

/*! @brief Updates the MouseScrollAction associated with scrolling a mouse wheel

    @param[in] new_scroll_action The new action to be associated with scrolling
*/
void input_set_mouse_scroll_action(MouseScrollAction new_scroll_action);

#endif
