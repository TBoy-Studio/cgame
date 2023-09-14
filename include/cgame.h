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
CGameError cgame_init();

void cgame_set_scene(CGameEntityScene *scene);

void cgame_set_window(CGameWindow *window);

/*
    Run the game, keeps going until window is closed
*/
CGameError cgame_run();
