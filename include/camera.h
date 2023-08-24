#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/types.h>
#include <cglm/vec3.h>
#include <cglm/cam.h>

typedef enum{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} Camera_MovementEnum;

typedef struct{
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 world_up;
    float yaw;
    float pitch;
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    float aspect_ratio;
    float near_plane_dist;
    float far_plane_dist;
} Camera;

/*
    Create a camera at position {pos_x, pos_y, pos_z}
    with world_up vector {up_x, up_y, up_z}
    and yaw and pitch. 
    Other values of camera will use default values
    Stores resulting camera in result
*/
void Camera_placeCamera(vec3 pos, vec3 up, vec3 front, float yaw, float pitch, float aspect_ratio);

/*
    Gets the projection matrix for a perspective view from this camera and stores it in result
*/
void Camera_getProjectionMatrix(mat4 result);

/*
    Gets the view matrix of the camera in it's current state and stores it in result
*/
void Camera_getViewMatrix(mat4 result);

/*
    Handles updates of camera position caused by keyboard input
*/
void Camera_processKeyboardMovement(Camera_MovementEnum movement, float delta_time);

/*
    Handles updates of camera pitch and yaw caused by mouse input
*/
void Camera_processMouseMovement(float x_offset, float y_offset, unsigned char constrain_pitch);

/*
    Handles updates to camera zoom caused by scrolling the mouse wheel
*/
void Camera_processMouseScroll(float y_offset);

#endif
