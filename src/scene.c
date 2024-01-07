#include <scene.h>

static char * _read_file(const char * file)
{
    // Sanity check
    if(!file) return 0;

    // Try opening file
    FILE* scene_file = fopen(file, "r"); 
    if(!scene_file) return 0;

    // Get shader file size
    unsigned long scene_file_size;    
    fseek(scene_file, 0, SEEK_END);
    scene_file_size = ftell(scene_file);
    rewind(scene_file);

    // Setup buffer for file contents
    char * scene_json = (char *)malloc(scene_file_size);
    scene_json[scene_file_size] = '\0';

    // Read the file into the buffer
    (void)fread(scene_json, sizeof(char), scene_file_size, scene_file);

    return scene_json;
}

/*
    Create a scene that can hold at most max_entities number of entities
*/
CGameScene _scene_create(size_t max_entities)
{
    CGameScene scene = {
        .pEntities = malloc(sizeof(CGameEntityEntry) * max_entities),
        .currentEntityCount = 0,
        .maxEntities = max_entities,
        .componentCount = MAX_COMPONENTS,
        .pComponentPools = malloc(sizeof(CGameComponentPool) * MAX_COMPONENTS)
    };
    
    for(CGameComponentType type = TRANSFORM; type < sizeof(component_sizes) / sizeof(size_t); type++)
    {
        scene.pComponentPools[type].componentType = type;
        scene.pComponentPools[type].pData = calloc(scene.maxEntities, component_sizes[type]);
    }
    return scene;
}

/*
    Get a pointer to the value at a specified index from this component pool
*/
static inline void *_get_value_from_component_pool(CGameComponentPool *pool, size_t index)
{
    return pool->pData + index * component_sizes[pool->componentType];
}

/*
    Free memory from this component pool
*/
static inline void _delete_component_pool(CGameComponentPool *pool)
{
    if(pool->pData) free(pool->pData);
}

void _print_parse_error()
{
    const char * err_ptr = cJSON_GetErrorPtr();
    if(err_ptr != NULL)
    {
        fprintf(stderr, "Error before: %s\n", err_ptr);
    }
}

/*
    Get a new EntityID from the scene
*/
CGameEntity cgame_entity_create(CGameScene * scene)
{   
    if(scene->currentEntityCount < scene->maxEntities)
    {
        scene->pEntities[scene->currentEntityCount].id = scene->currentEntityCount;
        scene->pEntities[scene->currentEntityCount].mask = 0;
        return scene->currentEntityCount++;
    }
    else
    {
        // TO DO: Throw Error, even better: dynamic sizing of scene
        return scene->maxEntities + 1;
    }
}

/*
    Add component to an entity
*/
void cgame_entity_add_component(CGameScene * scene, CGameEntity entity, CGameComponentType component)
{
    scene->pEntities[entity].mask |= (1 << component);    
}

/*
    Returns whether or not this entity has a certain component
*/
unsigned char cgame_entity_has_component(CGameScene * scene, CGameEntity entity, CGameComponentType component)
{
    return scene->pEntities[entity].mask & (1 << component);
}

unsigned char cgame_entity_is_archetype(CGameScene * scene, CGameEntity entity, CGameArchetype archetype)
{
    return (scene->pEntities[entity].mask & archetype) == archetype;
}

/*
    Get a pointer to the specified component
*/
void *cgame_entity_get_component(CGameScene * scene, CGameEntity entity, CGameComponentType component)
{
    return _get_value_from_component_pool(&scene->pComponentPools[component], entity);
}

/*
    Remove component from enemy
*/
void cgame_entity_remove_component(CGameScene * scene, CGameEntity entity, CGameComponentType component)
{
    scene->pEntities[entity].mask &= ~(1 << component);
}

static void _add_json_object_to_scene(cJSON * object, CGameScene * scene)
{
    cJSON * transform_json = NULL;
    cJSON * meshrenderer_json = NULL;

    CGameEntity entity = cgame_entity_create(scene);

    transform_json = cJSON_GetObjectItemCaseSensitive(object, "Transform");
    if(transform_json != NULL)
    {
        cJSON * position_json = cJSON_GetObjectItemCaseSensitive(transform_json, "position");
        cJSON * rotation_json = cJSON_GetObjectItemCaseSensitive(transform_json, "rotation");
        cJSON * scale_json = cJSON_GetObjectItemCaseSensitive(transform_json, "scale");        
        
        cgame_entity_add_component(scene, entity, TRANSFORM);
        CGameComponentTransform * transform = cgame_entity_get_component(scene, entity, TRANSFORM);

        transform->position[0] = cJSON_GetArrayItem(position_json, 0)->valuedouble;
        transform->position[1] = cJSON_GetArrayItem(position_json, 1)->valuedouble;
        transform->position[2] = cJSON_GetArrayItem(position_json, 2)->valuedouble;

        transform->rotation[0] = cJSON_GetArrayItem(rotation_json, 0)->valuedouble;
        transform->rotation[1] = cJSON_GetArrayItem(rotation_json, 1)->valuedouble;
        transform->rotation[2] = cJSON_GetArrayItem(rotation_json, 2)->valuedouble;

        transform->scale[0] = cJSON_GetArrayItem(scale_json, 0)->valuedouble;
        transform->scale[1] = cJSON_GetArrayItem(scale_json, 1)->valuedouble;
        transform->scale[2] = cJSON_GetArrayItem(scale_json, 2)->valuedouble;
    }

    meshrenderer_json = cJSON_GetObjectItemCaseSensitive(object, "MeshRenderer");
    if(meshrenderer_json != NULL)
    {
        // Get JSON data 
        cJSON * vertices_json = cJSON_GetObjectItemCaseSensitive(meshrenderer_json, "vertices");
        int array_size = cJSON_GetArraySize(vertices_json);

        // Add the component
        cgame_entity_add_component(scene, entity, MESHRENDERER);
        CGameComponentMeshRenderer * meshrenderer = cgame_entity_get_component(scene, entity, MESHRENDERER);

        // Get vertex data
        float * vertices = malloc(sizeof(float) * array_size);
        for(unsigned int i = 0; i < array_size; i++)
        {
            vertices[i] = cJSON_GetArrayItem(vertices_json, i)->valuedouble;
        }  

        // Create mesh   
        meshrenderer->mesh = malloc(sizeof(CGameModelMesh));  
        cgame_model_create_mesh((CGameModelVertex *)vertices, array_size * sizeof(float)/sizeof(CGameModelVertex), meshrenderer->mesh);        
    }
}

/*
    Free all allocated blocks associated with this scene
*/
void cgame_scene_delete(CGameScene * scene)
{
    for(CGameComponentType type = TRANSFORM; type < sizeof(component_sizes)/sizeof(size_t); type++)
    {
        _delete_component_pool(&scene->pComponentPools[type]);
    }
    free(scene->pEntities);
    free(scene->pComponentPools);
}

CGameScene cgame_scene_load(const char * file)
{
    // Setup vars
    const cJSON * name = NULL;
    const cJSON * objects = NULL;
    int status = 0;

    // Read file
    char * scene_json = _read_file(file);

    // Parsing
    cJSON * scene_object = cJSON_Parse(scene_json);
    if(scene_object == NULL)
    {
        _print_parse_error();   
        status = 0;
    }

    // Getting scene info
    name = cJSON_GetObjectItem(scene_object, "name");
    objects = cJSON_GetObjectItem(scene_object, "objects");    
    int object_count = cJSON_GetArraySize(objects);

    // Create scene with enough space to hold all objects
    CGameScene scene = _scene_create((size_t)object_count);

    // Loop through all objects and add them to the scene
    for(int i = 0; i < object_count; i++)
    {
        cJSON * object = cJSON_GetArrayItem(objects, i);
        _add_json_object_to_scene(object, &scene);
    }

    // Free memory
    free(scene_json);

    return scene;
}