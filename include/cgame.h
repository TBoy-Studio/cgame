#pragma once

#include <error.h>
#include <memory.h>
#include <controller.h>
#include <camera.h>
#include <input.h>
#include <shader.h>
#include <ecs.h>
#include <controller.h>

#include <cglm/cglm.h>

/*
    Initializes all subsystems in the cgame library
*/
void cgame_init();

void cgame_set_scene(CGameEntityScene *scene);

void cgame_set_window(CGameWindow *window);

void cgame_set_shader_program(CGameShaderProgram program);

void cgame_set_camera(CGameCamera *camera);

/*
    Run the game, keeps going until window is closed
*/
void cgame_run();

/*
    Closes the game and cleans up all resources associated with cgame
*/
void cgame_exit();
