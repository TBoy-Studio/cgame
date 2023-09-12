#include <tengine.h>

CGameError cgame_init()
{
    cgame_input_init();
}

CGameError cgame_run(CGameWindow *window)
{
    // Start capturing input from this window
    cgame_input_register_on_window(window);

    // Keep going until window should close
    while(!glfwWindowShouldClose(window->win))
    {
        // Handle Input
        cgame_input_handle_hold_down_keys();

        // Draw background
        cgame_window_draw_background(window);
        
        // Swap buffers
        glfwSwapBuffers(window->win);
        glfwPollEvents();
    }
}