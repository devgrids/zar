#pragma once

#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "../../data/Vertex.h"

namespace zar
{
    class ZAR_API GLMesh
    {
    public:
        ZAR_INLINE GLMesh(Vertices& vertices, Indices& indices, bool enable_bones = false);
        ZAR_INLINE ~GLMesh() = default;
        
        ZAR_INLINE GLMesh(const GLMesh&) = default;
        ZAR_INLINE GLMesh() = default;

        ZAR_INLINE void set_name(const char* name);
        ZAR_INLINE const std::string& name();

        ZAR_INLINE void set_material_index(uint32_t index);
        ZAR_INLINE int material_index();

        ZAR_INLINE void destroy_buffer();
        ZAR_INLINE void draw_elements(GLenum mode = GL_TRIANGLES);
        ZAR_INLINE void draw_arrays(GLenum mode = GL_TRIANGLES);

    private:
        uint32_t buffer_object_ = 0;
        uint32_t element_count_ = 0;
        uint32_t vertex_count_ = 0;
        uint32_t material_index_ = 0;
        std::string name_;
    };
}
#endif
