#pragma once

typedef unsigned int CGameEntity;
typedef unsigned int CGameEntityComponentMask;

typedef struct
{
    CGameEntity id;
    CGameEntityComponentMask mask;
} 
CGameEntityEntry;