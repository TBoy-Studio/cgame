#pragma once

#include <error.h>
#include <memory.h>
#include <file.h>
#include <camera.h>
#include <input.h>
#include <scene.h>
#include <system.h>
#include <shader.h>
#include <physics.h>

#include <cglm/cglm.h>

/*
    Initializes all subsystems in the cgame library
*/
void cgame_init();

/*
    Tell cgame which scene to render
*/
void cgame_set_scene(CGameScene *scene);

/*
    Tell cgame which window to render to
*/
void cgame_set_window(CGameWindow *window);

/*
    Tell cgame which shader program needs to be used to render
*/
void cgame_set_shader_program(CGameShaderProgram program);

/*
    Tell cgame which camera is used to render the scene from
*/
void cgame_set_camera(CGameCamera *camera);

/*
    Get the time between this frame and the last frame
*/
double cgame_time_get_delta_time();

/*
    Toggles rendering primitives as wireframes on/off
*/
void cgame_set_wireframe_mode(unsigned char enabled);

/*
    Run the game, keeps going until window is closed or cgame_exit() is called
*/
void cgame_run();

/*
    Closes the game and cleans up all resources associated with cgame
*/
void cgame_exit();
