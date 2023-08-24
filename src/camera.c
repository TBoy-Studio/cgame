#include <camera.h>

Camera camera;

static const float NEAR_PLANE_DIST = 0.1f;
static const float FAR_PLANE_DIST = 200.0f;
static const float SPEED = 5.0f;
static const float SENSITIVITY = 0.1f;
static const float ZOOM = 45.0f;

static void _updateCameraVectors(void)
{
    // Calculate new front vector
    camera.front[0] = cos(glm_rad(camera.yaw)) * cos(glm_rad(camera.pitch));
    camera.front[1] = sin(glm_rad(camera.pitch));
    camera.front[2] = sin(glm_rad(camera.yaw)) * cos(glm_rad(camera.pitch));
    glm_vec3_normalize(camera.front);

    // Use new front vector to calculate right and up vectors
    glm_vec3_cross(camera.front, camera.world_up, camera.right);
    glm_vec3_normalize(camera.right);

    glm_vec3_cross(camera.right, camera.front, camera.up);
    glm_vec3_normalize(camera.up);
}

void Camera_placeCamera(vec3 pos, vec3 up, vec3 front, float yaw, float pitch, float aspect_ratio)
{
    // Set vectors
    glm_vec3_copy(pos, camera.position);    
    glm_vec3_copy(up, camera.world_up);
    glm_vec3_copy(front, camera.front);
    
    // Setting fields
    camera.movement_speed = SPEED;
    camera.mouse_sensitivity = SENSITIVITY;
    camera.zoom = ZOOM;
    camera.yaw = yaw;
    camera.pitch = pitch;
    camera.aspect_ratio = aspect_ratio;
    camera.near_plane_dist = NEAR_PLANE_DIST;
    camera.far_plane_dist = FAR_PLANE_DIST;

    _updateCameraVectors(); // Make sure vectors are up to date
}

void Camera_getProjectionMatrix(mat4 result)
{
    glm_perspective(glm_rad(camera.zoom), camera.aspect_ratio, camera.near_plane_dist, camera.far_plane_dist, result);
}

void Camera_getViewMatrix(mat4 result)
{
    vec3 sum; // Temp vector
    
    // Add position and up vector
    glm_vec3_add(camera.position, camera.front, sum);

    // Calculate view matrix and store in result
    glm_lookat(camera.position, sum, camera.up, result);
}

void Camera_processKeyboardMovement(Camera_MovementEnum movement, float delta_time)
{
    // Calculate velocity
    float velocity = camera.movement_speed * delta_time;

    // Update position based on direction and speed
    if(movement == FORWARD)
        glm_vec3_muladds(camera.front,  velocity, camera.position);
    if(movement == BACKWARD)
        glm_vec3_muladds(camera.front, -velocity, camera.position);
    if(movement == LEFT)
        glm_vec3_muladds(camera.right, -velocity, camera.position);
    if(movement == RIGHT)
        glm_vec3_muladds(camera.right,  velocity, camera.position);
}

void Camera_processMouseMovement(float x_offset, float y_offset, unsigned char constrain_pitch)
{
    // Scale offsets by sensitivity
    x_offset *= camera.mouse_sensitivity;
    y_offset *= camera.mouse_sensitivity;

    // Add offsets to pitch and yaw
    camera.yaw += x_offset;
    camera.pitch += y_offset;

    // Check pitch constraint
    if (constrain_pitch) {
        if(camera.pitch > 89.0f)
            camera.pitch = 89.0f;
        if(camera.pitch < -89.0f)
            camera.pitch = -89.0f;
    }

    // Update camera vectors
    _updateCameraVectors();
}

void Camera_processMouseScroll(float y_offset)
{
    // Add offset to zoom
    camera.zoom -= y_offset;

    // Check zoom constraint
    if(camera.zoom < 1.0f)
        camera.zoom = 1.0f;
    if(camera.zoom > 45.0f)
        camera.zoom = 45.0f;
}
