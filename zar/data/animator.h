#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>

#include "animation.h"

namespace zar
{
    class ZAR_API Animator
    {
    public:
        ZAR_INLINE Animator(Animation* animation);
        ZAR_INLINE void update_animation(float dt);
        ZAR_INLINE void play_animation(Animation* p_animation);
        ZAR_INLINE void calculate_bone_transform(const AssimpNodeData* node, glm::mat4 parentTransform);
        ZAR_INLINE std::vector<glm::mat4> get_final_bone_matrices() const;
    private:
        std::vector<glm::mat4> m_final_bone_matrices_;
        Animation* m_current_animation_;
        float m_current_time_;
        float m_delta_time_;
    };
}
