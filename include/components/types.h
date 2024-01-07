#pragma once

typedef enum
{
    TRANSFORM,
    MESHRENDERER,
    CONTROLLER,
    RIGIDBODY
} 
CGameComponentType;

typedef enum
{
    RENDEROBJECT = (1 << TRANSFORM) | (1 << MESHRENDERER),
    PHYSICSOBJECT = (1 << TRANSFORM) | (1 << RIGIDBODY)
}
CGameArchetype;