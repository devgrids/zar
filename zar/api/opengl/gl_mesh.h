#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "gl_shader.h"
#include "../../data/material.h"
#include "../../data/vertex.h"

namespace zar
{
    class ZAR_API GLMesh
    {
    public:
        ZAR_INLINE GLMesh(const std::vector<Vertex> vertices, const std::vector<unsigned int> indices,
                          const std::vector<Material>
                          materials);
        ZAR_INLINE virtual void draw(const zar::GLShader& shader) const;
        ZAR_INLINE void destroy_buffer() const;
        ZAR_INLINE void draw_elements(GLenum mode = GL_TRIANGLES) const;
        ZAR_INLINE void draw_arrays(GLenum mode = GL_TRIANGLES) const;
    private:
        ZAR_INLINE void setup_mesh();
        unsigned int vbo_{}, ebo_{};
    public:
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Material> materials;
        GLuint vao{};
    };
}
