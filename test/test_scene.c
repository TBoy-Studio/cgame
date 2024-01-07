#include <cgame.h>
#include <assert.h>

int main()
{
    // Initialize cgame
    cgame_init();
    
    // Set up window and scene
    CGameWindow window = cgame_window_create_windowed("Cool Game", 1920, 1080);
    CGameScene scene = cgame_scene_load("/home/thijs/tboystudio/repos/TestGame/resources/scenes/test.scene");

    // Camera setup
    vec3 position = {0.0f, 0.0f, 3.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};
    CGameCamera camera = cgame_camera_create(position, up, -90.0f, 0.0f, 45.0f, ((float)window.width / (float)window.height));

    // Shader
    CGameShaderProgram shader = cgame_shader_create_program("/home/thijs/tboystudio/repos/TestGame/resources/shaders/vertex.glsl", 0, "/home/thijs/tboystudio/repos/TestGame/resources/shaders/fragment.glsl");

    cgame_set_window(&window);
    cgame_set_camera(&camera);
    cgame_set_shader_program(shader); 

    // Start the game loop
    cgame_run();

    // Clean up
    cgame_scene_delete(&scene);
    cgame_window_destroy(&window);
}