#include <ecs.h>

// The amount of components is dependent on the size of the mask
static const unsigned int MAX_COMPONENTS = sizeof(CGameEntityComponentMask) << 3;

static const size_t componentSizes[] = {
    sizeof(CGameComponentTransform),
    sizeof(CGameComponentMeshRenderer),
    sizeof(CGameComponentController),
    sizeof(CGameComponentRigidbody)
};

/*
    Get a pointer to the value at a specified index from this component pool
*/
static inline void *_get_value_from_component_pool(CGameComponentPool *pool, size_t index)
{
    return pool->pData + index * componentSizes[pool->componentType];
}

/*
    Free memory from this component pool
*/
static inline void _delete_component_pool(CGameComponentPool *pool)
{
    if(pool->pData) free(pool->pData);
}

/*
    Create a scene that can hold at most max_entities number of entities
*/
CGameEntityScene cgame_entity_scene_create(size_t max_entities)
{
    CGameEntityScene scene = {
        .pEntities = malloc(sizeof(CGameEntityEntry) * max_entities),
        .currentEntityCount = 0,
        .maxEntities = max_entities,
        .componentCount = MAX_COMPONENTS,
        .pComponentPools = malloc(sizeof(CGameComponentPool) * MAX_COMPONENTS)
    };
    for(CGameComponentType type = TRANSFORM; type < sizeof(componentSizes) / sizeof(size_t); type++)
    {
        scene.pComponentPools[type].componentType = type;
        scene.pComponentPools[type].pData = calloc(scene.maxEntities, componentSizes[type]);
    }
    return scene;
}

/*
    Get a new EntityID from the scene
*/
CGameEntity cgame_entity_create(CGameEntityScene *scene)
{   
    if(scene->currentEntityCount < scene->maxEntities)
    {
        scene->pEntities[scene->currentEntityCount].id = scene->currentEntityCount;
        scene->pEntities[scene->currentEntityCount].mask = 0;
        return scene->currentEntityCount++;
    }
    else
    {
        // TO DO: Throw Error
        return scene->maxEntities + 1;
    }
}

/*
    Add component to an entity
*/
void cgame_entity_add_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component)
{
    scene->pEntities[entity].mask |= (1 << component);    
}

/*
    Returns whether or not this entity has a certain component
*/
unsigned char cgame_entity_has_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component)
{
    return scene->pEntities[entity].mask & (1 << component);
}

unsigned char cgame_entity_is_archetype(CGameEntityScene *scene, CGameEntity entity, CGameArchetype archetype)
{
    return (scene->pEntities[entity].mask & archetype) == archetype;
}

/*
    Get a pointer to the specified component
*/
void *cgame_entity_get_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component)
{
    return _get_value_from_component_pool(&scene->pComponentPools[component], entity);
}

/*
    Remove component from enemy
*/
void cgame_entity_remove_component(CGameEntityScene *scene, CGameEntity entity, CGameComponentType component)
{
    scene->pEntities[entity].mask &= ~(1 << component);
}

/*
    Free all allocated blocks associated with this scene
*/
void cgame_entity_scene_delete(CGameEntityScene *scene)
{
    for(CGameComponentType type = TRANSFORM; type < sizeof(componentSizes)/sizeof(size_t); type++)
    {
        _delete_component_pool(&scene->pComponentPools[type]);
    }
    free(scene->pEntities);
    free(scene->pComponentPools);
}