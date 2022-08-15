#pragma once
#include <glm/ext/matrix_transform.hpp>

namespace zar
{
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // Default camera values
    constexpr float YAW = -90.0f;
    constexpr float PITCH = 0.0f;
    constexpr float SPEED = 2.5f;
    constexpr float SENSITIVITY = 0.1f;
    constexpr float ZOOM = 45.0f;

    class ZAR_API GLCamera
    {
    public:
        // camera Attributes
        glm::vec3 position{};
        glm::vec3 front;
        glm::vec3 up{};
        glm::vec3 right{};
        glm::vec3 world_up{};
        // euler Angles
        float yaw;
        float pitch;
        // camera options
        float movement_speed;
        float mouse_sensitivity;
        float zoom;

        GLCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                 float yaw = YAW, float pitch = PITCH);
        GLCamera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);
        glm::mat4 get_view_matrix() const;
        void process_keyboard(Camera_Movement direction, float delta_time);
        void process_mouse_movement(float xoffset, float yoffset, GLboolean constrain_pitch = true);
        void process_mouse_scroll(float yoffset);
    private:
        void update_camera_vectors();
    };
}
