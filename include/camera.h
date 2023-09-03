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
    // Movement values
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    vec3 world_up;
    float yaw;
    float pitch;
    float zoom;

    // Movement
    float movement_speed;
    float scroll_speed;
    float mouse_sensitivity;

    // Perspective configuration
    float aspect_ratio;
    float near_plane_dist;
    float far_plane_dist;

    // Configurable constraints for zoom and pitch
    float pitch_max;
    float pitch_min;
    float zoom_max;
    float zoom_min;
    unsigned char pitch_constrain;
    unsigned char zoom_constrain;
} Camera;

/*
    Place a camera at position pos with an up vector to specify which direction will be up
    Also configure yaw, pitch and zoom of camera on startup as well as the aspect ratio of
    the window being drawn to.
    Other values of camera will use default values on startup.
*/
Camera Camera_createCamera(vec3 pos, vec3 up, float yaw, float pitch, float zoom, float aspect_ratio);

/*
    Gets the projection matrix for a perspective view from this camera and stores it in result
*/
void Camera_getProjectionMatrix(Camera *camera, mat4 result);

/*
    Gets the view matrix of the camera in it's current state and stores it in result
*/
void Camera_getViewMatrix(Camera *camera, mat4 result);

/*
    Handles updates of camera position caused by keyboard input
*/
void Camera_processKeyboardMovement(Camera *camera, Camera_MovementEnum movement, float delta_time);

/*
    Handles updates of camera pitch and yaw caused by mouse input
*/
void Camera_processMouseMovement(Camera *camera, float x_offset, float y_offset);

/*
    Handles updates to camera zoom caused by scrolling the mouse wheel
*/
void Camera_processMouseScroll(Camera *camera, float y_offset);

/*
    Set a pitch constraint on this camera.
    Trying to move a camera beyond the limits set by pitch_max and pitch_min
    will force the pitch value to be set to the limit, never surpassing it.
*/
void Camera_setPitchConstraint(Camera *camera, float pitch_max, float pitch_min);

/*
    Set a zoom constraint on this camera.
    Trying to move a camera beyond the limits set by zoom_max and zoom_min
    will force the zoom value to be set to the limit, never surpassing it.
*/
void Camera_setZoomConstraint(Camera *camera, float zoom_max, float zoom_min);

/*
    Updates the camera speed for movements that influence the camera's position
*/
void Camera_setMovementSpeed(Camera *camera, float speed);

/*
    Updates the camera speed for scrolling movements
*/
void Camera_setScrollSpeed(Camera *camera, float speed);

/*
    Set the sensitivity for mouse movements influencing this camera
*/
void Camera_setSensitivity(Camera *camera, float sensitivity);

/*
    Set the aspect ratio of the camera (Calculated by dividing width by height)
*/
void Camera_setAspectRatio(Camera *camera, float aspect_ratio);

/*
    Set the near and far plane distances of this camera
*/
void Camera_setNearFarPlaneDistances(Camera *camera, float near, float far);

#endif
