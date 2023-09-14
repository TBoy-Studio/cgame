#pragma once

// 3rd party lib
#include <window.h>
#include <GLFW/glfw3.h>

// Including string.h for memory operations
#include <string.h>
#include <assert.h>

/*
    The callback function type that gets called when a key is
    pressed or released.
*/
typedef void (* CGameInputKeyActionFunc)(int action, int mods);

/*
    The callback function type that gets called when a mouse button 
    is pressed or released.
*/
typedef void (* CGameInputMouseButtonActionFunc)(int action, int mods);

/*
    The callback function type that gets called when a user scrolls
    the mouse wheel.
*/
typedef void (* CGameInputMouseScrollActionFunc)(double yoffset);

/*
    The callback function type that gets called when a user moves
    the cursor.
*/
typedef void (* CGameInputMouseCursorActionFunc)(double xpos, double ypos);

/*  
    Holds the callback function pointer, whether or not the press event should be repeated every
    frame (for holding down keys) and the current key state (GLFW_PRESS or GLFW_RELEASE)
*/
typedef struct{
    CGameInputKeyActionFunc action;
    int mods;
    unsigned char repeat;
    unsigned char last_key_action;
} CGameInputKeyActionContext;

/*
    Initializes the input library and clears all callback functions.
*/
void cgame_input_init();

/*
    Register callback functions on the specified window
    Should only be used internally by cgame.
*/
void cgame_input_register_on_window(CGameWindow *window);

/*
    Copies the specified array of keyactions over the array currently used by the window
    Can be used to update multiple keyactions in one go.
*/
void cgame_input_set_key_actions(CGameInputKeyActionContext key_actions[GLFW_KEY_LAST + 1]);

/*
    Registers the function pointer to a callback function that gets called
    when the specified key is pressed or released.
*/
void cgame_input_set_key_action(int key, CGameInputKeyActionFunc key_action, unsigned char repeat);

/*
    Copies the specified array of mouse button actions over the array
    currently used.
    Can be used to update multiple keyactions in one go.
*/
void cgame_input_set_mouse_button_actions(CGameInputMouseButtonActionFunc button_actions[GLFW_MOUSE_BUTTON_LAST + 1]);

/*
    Registers the function pointer to a callback function that gets called
    when the specified mouse button is pressed or released.
*/
void cgame_input_set_mouse_button_action(int button, CGameInputMouseButtonActionFunc button_action);

/*
    Registers the function pointer to a callback function that gets called
    when the mouse is scrolled.
*/
void cgame_input_set_scroll_action(CGameInputMouseScrollActionFunc scroll_action);

/*
    Registers the function pointer to a callback function that gets called
    when the mouse cursor has moved.
*/
void cgame_input_set_cursor_action(CGameInputMouseCursorActionFunc cursor_action);

/*
    Calls the callback function for all keys that are currently pressed
    and have (repeat = true) in the action context.
    This function should be called at the start of the main rendering loop
*/
void cgame_input_handle_hold_down_keys(void);

/*
    Get the mouse position from the previous frame.
    Updates after all input processing for current
    frame is done.
*/
void cgame_input_get_previous_cursor_position(float result[2]);
