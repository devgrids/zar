#include "GLShader.h"

namespace zar
{
    GLShader::GLShader(const char* vertex_path, const char* fragment_path)
    {
        std::string vertex_code;
        std::string fragment_code;
        std::ifstream v_shader_file;
        std::ifstream f_shader_file;

        v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        f_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            v_shader_file.open(vertex_path);
            f_shader_file.open(fragment_path);
            std::stringstream vShaderStream, fShaderStream;

            vShaderStream << v_shader_file.rdbuf();
            fShaderStream << f_shader_file.rdbuf();

            v_shader_file.close();
            f_shader_file.close();

            vertex_code = vShaderStream.str();
            fragment_code = fShaderStream.str();
        }
        catch (std::ifstream::failure& e)
        {
            spdlog::error("SHADER::FILE_NOT_SUCCESFULLY_READ: {}", e.what());
            spdlog::error("SHADER VERTEX PATH {}", vertex_path);
            spdlog::error("SHADER FRAGMENT PATH {}", fragment_path);
        }
        const char* v_shader_code = vertex_code.c_str();
        const char* f_shader_code = fragment_code.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &v_shader_code, nullptr);
        glCompileShader(vertex);
        check_compile_errors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &f_shader_code, nullptr);
        glCompileShader(fragment);
        check_compile_errors(fragment, "FRAGMENT");

        id = glCreateProgram();
        glAttachShader(id, vertex);
        glAttachShader(id, fragment);
        glLinkProgram(id);
        check_compile_errors(id, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    unsigned GLShader::get_id() const
    {
        return id;
    }

    void GLShader::use() const
    {
        glUseProgram(id);
    }

    void GLShader::set_bool(const std::string& name, const bool value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), static_cast<int>(value));
    }

    void GLShader::set_int(const std::string& name, const int value) const
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void GLShader::set_1f(const char* name, const float x) const
    {
        glUniform1f(glGetUniformLocation(id, name), x);
    }

    void GLShader::set_2f(const char* name, const float x, const float y) const
    {
        glUniform2f(glGetUniformLocation(id, name), x, y);
    }

    void GLShader::set_3f(const char* name, const float x, const float y, const float z) const
    {
        glUniform3f(glGetUniformLocation(id, name), x, y, z);
    }

    void GLShader::set_4f(const char* name, const float x, const float y, const float z, const float w) const
    {
        glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
    }

    void GLShader::set_vec2(const char* name, const glm::vec2& v) const
    {
        glUniform2f(glGetUniformLocation(id, name), v.x, v.y);
    }

    void GLShader::set_vec3(const char* name, const glm::vec3& v) const
    {
        glUniform3f(glGetUniformLocation(id, name), v.x, v.y, v.z);
    }

    void GLShader::set_vec4(const char* name, const glm::vec4& v) const
    {
        glUniform4f(glGetUniformLocation(id, name), v.x, v.y, v.z, v.w);
    }

    void GLShader::set_mat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void GLShader::set_sampler_2d(const char* name, uint32_t sampler, int unit) const
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, sampler);
        glUniform1i(glGetUniformLocation(id, name), unit);
    }

    void GLShader::check_compile_errors(const unsigned shader, const std::string& type) const
    {
        int success;
        char info_log[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, nullptr, info_log);
                spdlog::error("SHADER_COMPILATION_ERROR of type: {} {}", type, info_log);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, nullptr, info_log);
                spdlog::error("PROGRAM_LINKING_ERROR of type: {} {}", type, info_log);
            }
        }
    }
}
