#include <cgame.h>

extern const CGameSystem physics_system;

/*
    Applies a force to this rigidbody

    velocity += force * deltaTime / mass
*/
void cgame_physics_apply_force(CGameComponentRigidbody *rigidbody, vec3 force);

/*
    Applies an impulse to this rigidbody
    
    velocity += force / mass  
*/
void cgame_physics_apply_impulse(CGameComponentRigidbody *rigidbody, vec3 force);

/*
    Applies an acceleration to this rigidbody

    velocity += force * deltaTime
*/
void cgame_physics_apply_acceleration(CGameComponentRigidbody *rigidbody, vec3 force);

/*
    Applies a direct velocity change to this rigidbody

    velocity += force
*/
void cgame_physics_apply_velocity_change(CGameComponentRigidbody *rigidbody, vec3 force);

/*
    Sets the global gravity for all rigidbodies
*/
void cgame_physics_set_gravity(float new_gravity);