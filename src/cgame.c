#include <cgame.h>

static CGameWindow *current_window = 0;
static CGameEntityScene *current_scene = 0;

void cgame_init()
{
    cgame_input_init();
}

void cgame_set_scene(CGameEntityScene *scene)
{
    current_scene = scene;
}

void cgame_set_window(CGameWindow *window)
{
    current_window = window;
}

static void run_starts()
{
    for(CGameEntity entity = 0; entity < current_scene->currentEntityCount; entity++)
    {
        if(cgame_entity_has_component(current_scene, entity, CONTROLLER))
        {
            CGameComponentController *controller = cgame_entity_get_component(current_scene, entity, CONTROLLER);
            controller->start(current_window, current_scene, entity);
        }
    }
}

static void run_updates()
{
    for(CGameEntity entity = 0; entity < current_scene->currentEntityCount; entity++)
    {
        if(cgame_entity_has_component(current_scene, entity, CONTROLLER))
        {
            CGameComponentController *controller = cgame_entity_get_component(current_scene, entity, CONTROLLER);
            controller->update();
        }
    }
}

void cgame_run()
{
    // Programmer checks
    assert(current_scene);
    assert(current_window);

    // Start capturing input from this window
    cgame_input_register_on_window(current_window);

    // Run all registered start functions
    run_starts();

    // Keep going until window should close
    while(!glfwWindowShouldClose(current_window->win))
    {
        // Handle Input
        cgame_input_handle_hold_down_keys();

        // Draw background
        cgame_window_draw_background(current_window);

        // Updates should be called here
        run_updates();

        // Swap buffers
        glfwSwapBuffers(current_window->win);
        glfwPollEvents();
    }
}

void cgame_exit()
{
    glfwSetWindowShouldClose(current_window->win, GLFW_TRUE);
}