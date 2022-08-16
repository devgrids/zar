#pragma once

#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "../../zar.h"
#include <glm/glm.hpp>

namespace zar
{
    class ZAR_API GLShader
    {
    public:
        ZAR_INLINE GLShader(const char* vertex_path, const char* fragment_path);
        ZAR_INLINE unsigned get_id() const;
        ZAR_INLINE void use() const;

        ZAR_INLINE void set_bool(const std::string& name, bool value) const;
        ZAR_INLINE void set_int(const std::string& name, int value) const;

        // vectors & quaternion

        ZAR_INLINE void set_1f(const char* name, float x) const;
        ZAR_INLINE void set_2f(const char* name, float x, float y) const;
        ZAR_INLINE void set_3f(const char* name, float x, float y, float z) const;
        ZAR_INLINE void set_4f(const char* name, float x, float y, float z, float w) const;

        ZAR_INLINE void set_vec2(const char* name, const glm::vec2& v) const;
        ZAR_INLINE void set_vec3(const char* name, const glm::vec3& v) const;
        ZAR_INLINE void set_vec4(const char* name, const glm::vec4& v) const;

        ZAR_INLINE void set_mat4(const std::string& name, const glm::mat4& mat) const;
        ZAR_INLINE void set_sampler_2d(const char* name, uint32_t sampler, int unit = 0) const;
        
    private:
        ZAR_INLINE void check_compile_errors(unsigned int shader, const std::string& type) const;
        unsigned int id;
    };
}
#endif
