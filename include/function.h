#pragma once

#include <entity.h>

/*
    The type of function that gets called before the first frame is rendered
*/
typedef void (* CGameFuncStart)(CGameEntity entity);

/*
    The type of function that gets called every frame
*/
typedef void (* CGameFuncUpdate)(void);