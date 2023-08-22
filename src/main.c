#include <camera.h>
#include <shader.h>
#include <window.h>

int main(void){
    GLFWwindow* window = window_create("Test window");

    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    
    // Create camera
    Camera camera;
    camera_create(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, 0.0f, -90.0f, 0.0f, (float)width/(float)height, &camera);
    
    // Create shader program
    Shader shader = shader_create("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
    
    while(!glfwWindowShouldClose(window)){
        // TIMING

        // INPUT

        // BACKGROUND COLOR
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // USE SHADER
        shader_use(shader);

        // SET MVP MATRICES IN SHADER

        // DRAW
    }
    window_destroy(window);
    return 0;
}
