#pragma once

#include <error.h>
#include <memory.h>
#include <file.h>
#include <window.h>
#include <camera.h>
#include <input.h>
#include <shader.h>
#include <model.h>
#include <ecs.h>

#include <cglm/cglm.h>

/*
    Initializes all subsystems in the cgame library
*/
CGameError cgame_init();
