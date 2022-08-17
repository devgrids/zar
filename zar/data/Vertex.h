#pragma once

namespace zar
{
#define MAX_BONE_INFLUENCE 4
    
    struct Vertex
    {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 normal = glm::vec3(0.0f);
        glm::vec2 text_coords = glm::vec2(0.0f);
        glm::vec3 tangent = glm::vec3(0.0f);
        glm::vec3 bitangent = glm::vec3(0.0f);
        int bones[MAX_BONE_INFLUENCE];
        float weights[MAX_BONE_INFLUENCE];
    };

    // typedefs
    using Indices = std::vector<uint32_t>;
    using Vertices = std::vector<Vertex>;
}
