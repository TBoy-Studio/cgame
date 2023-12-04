#include <physics.h>

/*
    Steps for the physics system:
    - Apply forces
    - Update positions and velocities
    - Detect collisions
    - Solve constraints
    - Display Results (not really physics)
*/

static float gravity = 9.81;

static CGameEntityScene *p_scene;

static void init(CGameEntityScene *scene)
{
    p_scene = scene;
}

static inline void compute_force(CGameComponentRigidbody *rigidbody, vec3 result)
{
    result[0] = 0.0f;
    result[1] = rigidbody->mass * -gravity;
    result[2] = 0.0f;
}

static void run_physics_system()
{
    float deltaTime = cgame_time_get_delta_time();

    for(size_t i = 0; i < p_scene->currentEntityCount; i++)
    {
        if(cgame_entity_is_archetype(p_scene, p_scene->pEntities[i].id, PHYSICSOBJECT))
        {
            CGameComponentTransform *transform = cgame_entity_get_component(p_scene, p_scene->pEntities[i].id, TRANSFORM);
            CGameComponentRigidbody *rigidbody = cgame_entity_get_component(p_scene, p_scene->pEntities[i].id, RIGIDBODY);

            vec3 force, acceleration;
            compute_force(rigidbody, force);
            glm_vec3_divs(force, rigidbody->mass, acceleration);
            glm_vec3_muladds(acceleration, deltaTime, rigidbody->velocity);
            glm_vec3_muladds(rigidbody->velocity, deltaTime, transform->position);
        }
    }
}

void cgame_physics_apply_force(CGameComponentRigidbody *rigidbody, vec3 force)
{
    float delta_time = cgame_time_get_delta_time();
    vec3 acceleration;
    glm_vec3_divs(force, rigidbody->mass, acceleration);
    glm_vec3_muladds(acceleration, delta_time, rigidbody->velocity);
}

void cgame_physics_apply_impulse(CGameComponentRigidbody *rigidbody, vec3 force)
{
    vec3 impulse;
    glm_vec3_divs(force, rigidbody->mass, impulse);
    glm_vec3_add(rigidbody->velocity, impulse, rigidbody->velocity);
}

void cgame_physics_apply_acceleration(CGameComponentRigidbody *rigidbody, vec3 force)
{
    float delta_time = cgame_time_get_delta_time();
    glm_vec3_muladds(force, delta_time, rigidbody->velocity); 
}

void cgame_physics_apply_velocity_change(CGameComponentRigidbody *rigidbody, vec3 force)
{
    glm_vec3_add(rigidbody->velocity, force, rigidbody->velocity);
}

void cgame_physics_set_gravity(float new_gravity)
{
    gravity = new_gravity;
}

const CGameSystem physics_system = {
    .init = init,
    .update = run_physics_system
};