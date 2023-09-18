#include <cgame.h>

static CGameWindow *current_window = 0;
static CGameEntityScene *current_scene = 0;
static CGameShaderProgram current_program = 0;
static CGameCamera *current_camera = 0;

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

void cgame_set_shader_program(CGameShaderProgram program)
{
    current_program = program;
}

void cgame_set_camera(CGameCamera *camera)
{
    current_camera = camera;
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

static void render_objects()
{
    cgame_shader_use_program(current_program);
    mat4 projection, view;

    cgame_camera_get_projection(current_camera, projection);
    cgame_camera_get_view(current_camera, view);

    cgame_shader_set_mat4(current_program, "projection", projection);
    cgame_shader_set_mat4(current_program, "view", view);

    for(CGameEntity entity = 0; entity < current_scene->currentEntityCount; entity++)
    {
        if(cgame_entity_is_archetype(current_scene, entity, RENDEROBJECT))
        {
            CGameComponentMeshRenderer *mesh = cgame_entity_get_component(current_scene, entity, MESHRENDERER);
            CGameComponentTransform *transform = cgame_entity_get_component(current_scene, entity, TRANSFORM);

            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, transform->position);
            cgame_shader_set_mat4(current_program, "model", model);

            cgame_model_draw_mesh(mesh->mesh);
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

        // Controller updates will be called here
        run_updates();

        // Rendering
        if(current_program && current_camera) render_objects();

        // Swap buffers
        glfwSwapBuffers(current_window->win);
        glfwPollEvents();
    }
}

void cgame_exit()
{
    glfwSetWindowShouldClose(current_window->win, GLFW_TRUE);
}