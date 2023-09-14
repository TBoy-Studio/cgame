#pragma once

#include <ecs.h>

typedef struct
{
    CGameFuncStart start;
    CGameFuncUpdate update;
}
CGameController;

void cgame_controller_register(const CGameController *controller, CGameEntityScene *scene);