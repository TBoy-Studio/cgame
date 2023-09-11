#pragma once

#include <cglm/types.h>
#include <cglm/vec3.h>
#include <cglm/cam.h>

typedef enum{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} CGameCameraMovement;

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
} CGameCamera;

/*
    Place a camera at position pos with an up vector to specify which direction will be up
    Also configure yaw, pitch and zoom of camera on startup as well as the aspect ratio of
    the window being drawn to.
    Other values of camera will use default values on startup.
*/
CGameCamera cgame_camera_create(vec3 pos, vec3 up, float yaw, float pitch, float zoom, float aspect_ratio);

/*
    Gets the projection matrix for a perspective view from this camera and stores it in result
*/
void cgame_camera_get_projection(CGameCamera *camera, mat4 result);

/*
    Gets the view matrix of the camera in it's current state and stores it in result
*/
void cgame_camera_get_view(CGameCamera *camera, mat4 result);

/*
    Handles updates of camera position caused by keyboard input
*/
void cgame_camera_handle_keyboard(CGameCamera *camera, CGameCameraMovement movement, float delta_time);

/*
    Handles updates of camera pitch and yaw caused by mouse input
*/
void cgame_camera_handle_cursor(CGameCamera *camera, float x_offset, float y_offset);

/*
    Handles updates to camera zoom caused by scrolling the mouse wheel
*/
void cgame_camera_handle_scroll(CGameCamera *camera, float y_offset);

/*
    Set a pitch constraint on this camera.
    Trying to move a camera beyond the limits set by pitch_max and pitch_min
    will force the pitch value to be set to the limit, never surpassing it.
*/
void cgame_camera_set_constraint_pitch(CGameCamera *camera, float pitch_max, float pitch_min);

/*
    Set a zoom constraint on this camera.
    Trying to move a camera beyond the limits set by zoom_max and zoom_min
    will force the zoom value to be set to the limit, never surpassing it.
*/
void cgame_camera_set_constraint_zoom(CGameCamera *camera, float zoom_max, float zoom_min);

/*
    Updates the camera speed for movements that influence the camera's position
*/
void cgame_camera_set_speed_movement(CGameCamera *camera, float speed);

/*
    Updates the camera speed for scrolling movements
*/
void cgame_camera_set_speed_scroll(CGameCamera *camera, float speed);

/*
    Set the sensitivity for mouse movements influencing this camera
*/
void cgame_camera_set_sensitivity(CGameCamera *camera, float sensitivity);

/*
    Set the aspect ratio of the camera (Calculated by dividing width by height)
*/
void cgame_camera_set_aspect(CGameCamera *camera, float aspect_ratio);

/*
    Set the near and far plane distances of this camera
*/
void cgame_camera_set_near_far_plane_distances(CGameCamera *camera, float near, float far);
