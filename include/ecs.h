#pragma once

#include <cglm/types.h>
#include <stdlib.h>
#include <model.h>
#include <window.h>

typedef unsigned int CGameEntity;

typedef unsigned int CGameEntityComponentMask;

typedef struct
{
    CGameEntity id;
    CGameEntityComponentMask mask;
} 
CGameEntityEntry;

typedef struct
{
    vec3 position;
    vec3 rotation;
    vec3 scale;
} 
CGameComponentTransform;

typedef struct
{
    CGameModelMesh *mesh;
} 
CGameComponentMeshRenderer;

typedef struct
{
    vec3 velocity;
    float mass;
}
CGameComponentRigidbody;

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

typedef struct
{
    CGameComponentType componentType;
    void *pData;
} 
CGameComponentPool;

typedef struct
{
    // Constraints
    const unsigned int maxEntities;

    // Entities
    CGameEntityEntry *pEntities;
    unsigned int currentEntityCount;
    
    // Components
    CGameComponentPool *pComponentPools;
    unsigned int componentCount;
} 
CGameEntityScene;

/*
    The type of function that gets called before the first frame is rendered
*/
typedef void (* CGameFuncStart)(CGameWindow *window, CGameEntityScene *scene, CGameEntity entity);

/*
    The type of function that gets called every frame
*/
typedef void (* CGameFuncUpdate)(void);

typedef struct
{
    CGameFuncStart start;
    CGameFuncUpdate update;
}
CGameComponentController;

/*
    Create a scene that can hold at most max_entities number of entities
*/
CGameEntityScene cgame_entity_scene_create(size_t max_entities);

/*
    Get a new EntityID from the scene
*/
CGameEntity cgame_entity_create(CGameEntityScene *scene);

/*
    Add component to an entity
*/
void cgame_entity_add_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component);

/*
    Returns whether or not this entity has a certain component
*/
unsigned char cgame_entity_has_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component);

/*
    Returns whether or not this entity is of a certain archetype (has a specific set of components)
*/
unsigned char cgame_entity_is_archetype(CGameEntityScene *scene, CGameEntity entity, CGameArchetype archetype);

/*
    Get a pointer to the specified component
*/
void *cgame_entity_get_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component);

/*
    Remove component from enemy
*/
void cgame_entity_remove_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component);

/*
    Free all allocated blocks associated with this scene
*/
void cgame_entity_scene_delete(CGameEntityScene *scene);