#pragma once

/*
    The type of function that gets called when a system is called to initialize
*/
typedef void (* CGameFuncSystemInit)();

/*
    The type of function that gets called on a system every frame and updates it's state
*/
typedef void (* CGameFuncSystemUpdate)(void);

typedef struct
{
    CGameFuncSystemInit init;
    CGameFuncSystemUpdate update;
}
CGameSystem;