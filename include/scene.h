#pragma once

#include <file.h>
#include <entity.h>
#include <components/components.h>
#include <cJSON/cJSON.h>

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
CGameScene;

/*
    Loads a scene from a file and creates a scene using the ecs system
*/
CGameScene cgame_scene_load(const char * file);

/*
    Free all allocated blocks associated with this scene
*/
void cgame_scene_delete(CGameScene * scene);

/*
    Add component to an entity
*/
void cgame_entity_add_component(CGameScene * scene, CGameEntity entity, CGameComponentType component);

/*
    Returns whether or not this entity has a certain component
*/
unsigned char cgame_entity_has_component(CGameScene * scene, CGameEntity entity, CGameComponentType component);

/*
    Returns whether or not this entity is of a certain archetype (has a specific set of components)
*/
unsigned char cgame_entity_is_archetype(CGameScene * scene, CGameEntity entity, CGameArchetype archetype);

/*
    Get a pointer to the specified component
*/
void *cgame_entity_get_component(CGameScene * scene, CGameEntity entity, CGameComponentType component);

/*
    Remove component from entity
*/
void cgame_entity_remove_component(CGameScene * scene, CGameEntity entity, CGameComponentType component);


