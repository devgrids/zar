#include "gl_camera.h"

#include <glm/ext/matrix_clip_space.hpp>

zar::GLCamera::GLCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
    this->position = position;
    world_up = up;
    this->yaw = yaw;
    this->pitch = pitch;
    update_camera_vectors();
}

zar::GLCamera::GLCamera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw,
                        float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
{
    position = glm::vec3(pos_x, pos_y, pos_z);
    world_up = glm::vec3(up_x, up_y, up_z);
    this->yaw = yaw;
    this->pitch = pitch;
    update_camera_vectors();
}

zar::GLCamera::~GLCamera()
{
    spdlog::info("~GLCamera() destroyed!");
}

glm::mat4 zar::GLCamera::get_view_matrix() const
{
    return glm::lookAt(position, position + front, up);
}

glm::mat4 zar::GLCamera::get_projection_matrix(const float aspect) const
{
    return glm::perspective(glm::radians(zoom), aspect, 0.1f,
                            100.0f);
}

void zar::GLCamera::process_keyboard(const Camera_Movement direction, const float delta_time)
{
    const float velocity = movement_speed * delta_time;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

void zar::GLCamera::process_mouse_movement(float xoffset, float yoffset, const GLboolean constrain_pitch)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrain_pitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    update_camera_vectors();
}

void zar::GLCamera::process_mouse_scroll(const float yoffset)
{
    zoom -= static_cast<float>(yoffset);
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

void zar::GLCamera::update_camera_vectors()
{
    glm::vec3 _front;
    _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    _front.y = sin(glm::radians(pitch));
    _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(_front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}
