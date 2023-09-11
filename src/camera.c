#include <camera.h>

static const float NEAR_PLANE_DIST = 0.1f;
static const float FAR_PLANE_DIST = 200.0f;
static const float MOVEMENT_SPEED = 5.0f;
static const float SCROLL_SPEED = 1.0f;
static const float SENSITIVITY = 0.1f;

static inline void _update_camera_vectors(CGameCamera* camera)
{
    // Calculate new front vector
    camera->front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    camera->front[1] = sin(glm_rad(camera->pitch));
    camera->front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_vec3_normalize(camera->front);

    // Use new front vector to calculate right and up vectors
    glm_vec3_cross(camera->front, camera->world_up, camera->right);
    glm_vec3_normalize(camera->right);

    glm_vec3_cross(camera->right, camera->front, camera->up);
    glm_vec3_normalize(camera->up);
}

CGameCamera cgame_camera_create(vec3 pos, vec3 up, float yaw, float pitch, float zoom, float aspect_ratio)
{
    CGameCamera camera;
    
    // Set vectors
    glm_vec3_copy(pos, camera.position);    
    glm_vec3_copy(up, camera.world_up);
    
    // Setting fields
    camera.movement_speed = MOVEMENT_SPEED;
    camera.scroll_speed = SCROLL_SPEED;
    camera.mouse_sensitivity = SENSITIVITY;
    camera.zoom = zoom;
    camera.yaw = yaw;
    camera.pitch = pitch;
    camera.aspect_ratio = aspect_ratio;
    camera.near_plane_dist = NEAR_PLANE_DIST;
    camera.far_plane_dist = FAR_PLANE_DIST;

    // Disable constraints
    camera.pitch_constrain = false;
    camera.zoom_constrain = false;

    _update_camera_vectors(&camera); // Make sure vectors are up to date

    return camera;
}

void cgame_camera_get_projection(CGameCamera *camera, mat4 result)
{
    glm_perspective(glm_rad(camera->zoom), camera->aspect_ratio, camera->near_plane_dist, camera->far_plane_dist, result);
}

void cgame_camera_get_view(CGameCamera *camera, mat4 result)
{
    vec3 sum; // Temp vector
    
    // Add position and up vector
    glm_vec3_add(camera->position, camera->front, sum);

    // Calculate view matrix and store in result
    glm_lookat(camera->position, sum, camera->up, result);
}

void cgame_camera_handle_keyboard(CGameCamera *camera, CGameCameraMovement movement, float delta_time)
{
    // Calculate velocity
    float velocity = camera->movement_speed * delta_time;

    // Update position based on direction and speed
    if(movement == FORWARD)
        glm_vec3_muladds(camera->front,  velocity, camera->position);
    else if(movement == BACKWARD)
        glm_vec3_muladds(camera->front, -velocity, camera->position);
    else if(movement == LEFT)
        glm_vec3_muladds(camera->right, -velocity, camera->position);
    else if(movement == RIGHT)
        glm_vec3_muladds(camera->right,  velocity, camera->position);
}

void cgame_camera_handle_cursor(CGameCamera *camera, float x_offset, float y_offset)
{
    // Scale offsets by sensitivity
    x_offset *= camera->mouse_sensitivity;
    y_offset *= camera->mouse_sensitivity;

    // Add offsets to pitch and yaw
    camera->yaw += x_offset;
    camera->pitch += y_offset;

    // Apply pitch constraint
    if(camera->pitch_constrain)
        if(camera->pitch > camera->pitch_max) 
            camera->pitch = camera->pitch_max;
        else if(camera->pitch < camera->pitch_min) 
            camera->pitch = camera->pitch_min;

    // Update camera vectors
    _update_camera_vectors(camera);
}

void cgame_camera_handle_scroll(CGameCamera *camera, float y_offset)
{
    // Add offset to zoom
    camera->zoom -= y_offset * camera->scroll_speed;

    // Apply zoom constraint
    if(camera->zoom_constrain)
        if(camera->zoom > camera->zoom_max)
            camera->zoom = camera->zoom_max;
        if(camera->zoom < camera->zoom_min)
            camera->zoom = camera->zoom_min;
}

void cgame_camera_set_constraint_pitch(CGameCamera *camera, float pitch_max, float pitch_min)
{
    camera->pitch_constrain = true;
    camera->pitch_max = pitch_max;
    camera->pitch_min = pitch_min;
}

void cgame_camera_set_constraint_zoom(CGameCamera *camera, float zoom_max, float zoom_min)
{
    camera->zoom_constrain = true;
    camera->zoom_max = zoom_max;
    camera->zoom_min = zoom_min;
}

void cgame_camera_set_speed_movement(CGameCamera *camera, float speed)
{
    camera->movement_speed = speed;
}

void cgame_camera_set_speed_scroll(CGameCamera *camera, float speed)
{
    camera->scroll_speed = speed;
}

void cgame_camera_set_sensitivity(CGameCamera *camera, float sensitivity)
{
    camera->mouse_sensitivity = sensitivity;
}

void cgame_camera_set_aspect(CGameCamera *camera, float aspect_ratio)
{
    camera->aspect_ratio = aspect_ratio;
}

void cgame_camera_set_near_far_plane_distances(CGameCamera *camera, float near, float far)
{
    camera->near_plane_dist = near;
    camera->far_plane_dist = far;
}
