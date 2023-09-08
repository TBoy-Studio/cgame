#ifndef ECS_H
#define ECS_H

#include <cglm/types.h>
#include <stdlib.h>
#include <model.h>

typedef unsigned int EntityID;

typedef unsigned int EntityComponentMask;

typedef struct{
    EntityID id;
    EntityComponentMask mask;
} EntityEntry;

typedef struct{
    vec3 position;
    vec3 rotation;
    vec3 scale;
} Transform;

typedef struct
{
    Model_Mesh *mesh;
} 
MeshRenderer;

typedef enum{
    TRANSFORM,
    MESHRENDERER
} EComponentType;

typedef struct{
    EComponentType componentType;
    unsigned char *pData;
} ComponentPool;

typedef struct{
    // Constraints
    const unsigned int maxEntities;

    // Entities
    EntityEntry *pEntities;
    unsigned int currentEntityCount;
    
    // Components
    ComponentPool *pComponentPools;
    unsigned int componentCount;
} Scene;

/*
    Get a pointer to the value at a specified index from this component pool
*/
void *getValueFromComponentPool(ComponentPool *pool, size_t index);

/*
    Free memory from this component pool
*/
void deleteComponentPool(ComponentPool *pool);

/*
    Get a new EntityID from the scene
*/
EntityID createNewEntity(Scene *scene);

/*
    Returns whether or not this entity has a certain component
*/
unsigned char hasEntityComponent(Scene *scene, EntityID entity, EComponentType component);

/*
    Add component to an entity
*/
void addEntityComponent(Scene *scene, EntityID entity, EComponentType component);

/*
    Remove component from enemy
*/
void removeEntityComponent(Scene *scene, EntityID entity, EComponentType component);

/*
    Get a pointer to the specified component
*/
void *getEntityComponent(Scene* scene, EntityID entity, EComponentType component);

/*
    Create a scene that can hold at most max_entities number of entities
*/
Scene createScene(size_t max_entities);

/*
    Free all allocated blocks associated with this scene
*/
void deleteScene(Scene *scene);

#endif