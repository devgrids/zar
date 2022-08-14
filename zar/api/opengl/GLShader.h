#pragma once

#ifndef GL_SHADER_H
#define GL_SHADER_H

#include "../../zar.h"

namespace zar
{
    class ZAR_API GLShader
    {
    public:
        GLShader(const char* vertex_path, const char* fragment_path);
        void use() const;
        void set_bool(const std::string& name, bool value) const;
        void set_int(const std::string& name, int value) const;
        void set_float(const std::string& name, float value) const;
    private:
        void check_compile_errors(unsigned int shader, const std::string& type) const;
    public:
        unsigned int id;
    };
}
#endif
