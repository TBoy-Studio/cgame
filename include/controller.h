#pragma once

#include <ecs.h>

typedef struct
{
    CGameFuncStart start;
    CGameFuncUpdate update;
}
CGameController;

/*
    Registers this controller in cgame, so it's functions get called
*/
void cgame_controller_register(const CGameController *controller, CGameEntityScene *scene);