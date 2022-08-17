#pragma once

#include<assimp/quaternion.h>
#include<assimp/vector3.h>
#include<assimp/matrix4x4.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

namespace zar
{
    class ZAR_API AssimpGLMHelpers
    {
    public:
        static inline glm::mat4 convert_matrix_to_glm_format(const aiMatrix4x4& from);
        static inline glm::vec3 get_glm_vec(const aiVector3D& vec);
        static inline glm::quat get_glm_quat(const aiQuaternion& p_orientation);
    };
}
