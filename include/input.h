#ifndef INPUT_H
#define INPUT_H

// 3rd party lib
#include <window.h>
#include <GLFW/glfw3.h>

// Including string.h for memory operations
#include <string.h>

/*
    The callback function type that gets called when a key is
    pressed or released.
*/
typedef void (* Input_KeyActionFunc)(int action, int mods);

/*
    The callback function type that gets called when a mouse button 
    is pressed or released.
*/
typedef void (* Input_MouseButtonActionFunc)(int action, int mods);

/*
    The callback function type that gets called when a user scrolls
    the mouse wheel.
*/
typedef void (* Input_MouseScrollActionFunc)(double yoffset);

/*
    The callback function type that gets called when a user moves
    the cursor.
*/
typedef void (* Input_MouseCursorActionFunc)(double xpos, double ypos);

/*  
    Holds the callback function pointer, whether or not the press event should be repeated every
    frame (for holding down keys) and the current key state (GLFW_PRESS or GLFW_RELEASE)
*/
typedef struct{
    Input_KeyActionFunc action;
    int mods;
    unsigned char repeat;
    unsigned char last_key_action;
} Input_KeyActionContext;

/*
    Initializes the input library and clears all callback functions.
*/
void Input_init(Window *window);

/*
    Copies the specified array of keyactions over the array currently used by the window
    Can be used to update multiple keyactions in one go.
*/
void Input_setKeyActions(Input_KeyActionContext key_actions[GLFW_KEY_LAST + 1]);

/*
    Registers the function pointer to a callback function that gets called
    when the specified key is pressed or released.
*/
void Input_setKeyAction(int key, Input_KeyActionFunc key_action, unsigned char repeat);

/*
    Copies the specified array of mouse button actions over the array
    currently used.
    Can be used to update multiple keyactions in one go.
*/
void Input_setMouseButtonActions(Input_MouseButtonActionFunc button_actions[GLFW_MOUSE_BUTTON_LAST + 1]);

/*
    Registers the function pointer to a callback function that gets called
    when the specified mouse button is pressed or released.
*/
void Input_setMouseButtonAction(int button, Input_MouseButtonActionFunc button_action);

/*
    Registers the function pointer to a callback function that gets called
    when the mouse is scrolled.
*/
void Input_setMouseScrollAction(Input_MouseScrollActionFunc scroll_action);

/*
    Registers the function pointer to a callback function that gets called
    when the mouse cursor has moved.
*/
void Input_setMouseCursorAction(Input_MouseCursorActionFunc cursor_action);

/*
    Calls the callback function for all keys that are currently pressed
    and have (repeat = true) in the action context.
    This function should be called at the start of the main rendering loop
*/
void Input_handleHoldDownKeys(void);

/*
    Get the mouse position from the previous frame.
    Updates after all input processing for current
    frame is done.
*/
void Input_getPrevMouseCursorPosition(float result[2]);


#endif
