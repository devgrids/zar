#pragma once

namespace zar
{
    struct ZAR_API Vertex
    {
        glm::vec3 position	= glm::vec3(0.0f);
        glm::vec3 normal	= glm::vec3(0.0f);
        glm::vec2 text_coords = glm::vec2(0.0f);
        glm::vec3 tangent	= glm::vec3(0.0f);
        glm::vec3 bitangent = glm::vec3(0.0f);
        glm::ivec4 bones	= glm::ivec4(-1);
        glm::vec4 weights	= glm::vec4(0.0f);

        ZAR_INLINE void set_bone_data(int id, float weight) ;
    };

    // typedefs
    using Indices = std::vector<uint32_t>;
    using Vertices = std::vector<Vertex>;
}
