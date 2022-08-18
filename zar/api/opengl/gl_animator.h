#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>

#include "gl_animation.h"


namespace zar
{
    class ZAR_API GLAnimator
    {
    public:
        ZAR_INLINE GLAnimator(GLAnimation* animation);
        ZAR_INLINE void update_animation(float dt);
        ZAR_INLINE void play_animation(GLAnimation* p_animation);
        ZAR_INLINE void calculate_bone_transform(const AssimpNodeData* node, glm::mat4 parentTransform);
        ZAR_INLINE std::vector<glm::mat4> get_final_bone_matrices() const;
    private:
        std::vector<glm::mat4> m_final_bone_matrices_;
        GLAnimation* m_current_animation_;
        float m_current_time_;
        float m_delta_time_;
    };
}
