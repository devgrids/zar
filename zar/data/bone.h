#pragma once

/* Container for bone data */

#include <vector>
#include <assimp/scene.h>
#include <list>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "assimp_glm_helpers.h"

namespace zar
{
    struct KeyPosition
    {
        glm::vec3 position;
        float timeStamp;
    };

    struct KeyRotation
    {
        glm::quat orientation;
        float timeStamp;
    };

    struct KeyScale
    {
        glm::vec3 scale;
        float timeStamp;
    };

    class ZAR_API Bone
    {
    public:
        Bone(std::string name, int id, const aiNodeAnim* channel);
        void update(float animation_time);
        glm::mat4 get_local_transform() const;
        std::string get_bone_name() const { return m_name_; }
        int get_bone_id() const;
        int get_position_index(float animation_time) const;
        int get_rotation_index(float animation_time) const;
        int get_scale_index(float animation_time) const;
    private:
        float get_scale_factor(float last_time_stamp, float next_time_stamp, float animation_time);
        glm::mat4 interpolate_position(float animation_time);
        glm::mat4 interpolate_rotation(float animation_time);
        glm::mat4 interpolate_scaling(float animation_time);

        std::vector<KeyPosition> m_positions_;
        std::vector<KeyRotation> m_rotations_;
        std::vector<KeyScale> m_scales_;
        int m_num_positions_;
        int m_num_rotations_;
        int m_num_scalings_;

        glm::mat4 m_local_transform_;
        std::string m_name_;
        int m_id_;
    };
}
