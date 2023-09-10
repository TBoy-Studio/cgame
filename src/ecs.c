#include <ecs.h>

// The amount of components is dependent on the size of the mask
static const unsigned int MAX_COMPONENTS = sizeof(EntityComponentMask) << 3;

static const size_t componentSizes[] = {
    sizeof(Transform),
    sizeof(MeshRenderer)
};

/*
    Get a pointer to the value at a specified index from this component pool
*/
void *getValueFromComponentPool(ComponentPool *pool, size_t index)
{
    return pool->pData + index * componentSizes[pool->componentType];
}

/*
    Free memory from this component pool
*/
void deleteComponentPool(ComponentPool *pool)
{
    free(pool->pData);
}

/*
    Get a new EntityID from the scene
*/
EntityID createNewEntity(Scene *scene)
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
    Returns whether or not this entity has a certain component
*/
unsigned char hasEntityComponent(Scene *scene, EntityID entity, EComponentType component)
{
    return scene->pEntities[entity].mask & (1 << component);
}

/*
    Add component to an entity
*/
void addEntityComponent(Scene *scene, EntityID entity, EComponentType component)
{
    scene->pEntities[entity].mask |= (1 << component);    
}

/*
    Remove component from enemy
*/
void removeEntityComponent(Scene *scene, EntityID entity, EComponentType component)
{
    scene->pEntities[entity].mask &= ~(1 << component);
}

/*
    Get a pointer to the specified component
*/
void *getEntityComponent(Scene* scene, EntityID entity, EComponentType component)
{
    return getValueFromComponentPool(&scene->pComponentPools[component], entity);
}

/*
    Create a scene that can hold at most max_entities number of entities
*/
Scene createScene(size_t max_entities)
{
    Scene scene = {
        .pEntities = malloc(sizeof(EntityEntry) * max_entities),
        .currentEntityCount = 0,
        .maxEntities = max_entities,
        .componentCount = MAX_COMPONENTS,
        .pComponentPools = malloc(sizeof(ComponentPool) * MAX_COMPONENTS)
    };
    for(EComponentType type = TRANSFORM; type < sizeof(componentSizes) / sizeof(size_t); type++)
    {
        scene.pComponentPools[type].componentType = type;
        scene.pComponentPools[type].pData = calloc(scene.maxEntities, componentSizes[type]);
    }
    return scene;
}

/*
    Free all allocated blocks associated with this scene
*/
void deleteScene(Scene *scene)
{
    for(unsigned int i = 0; i < scene->componentCount; i++)
    {
        deleteComponentPool(&scene->pComponentPools[i]);
    }
    free(scene->pEntities);
    free(scene->pComponentPools);
}