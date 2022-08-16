#pragma once

namespace zar
{
    class ZAR_API GLTexture
    {
    public:
        ZAR_INLINE GLTexture();
    protected:
        ZAR_INLINE ~GLTexture() = default;
    public:
        ZAR_INLINE GLTexture(const GLTexture&) = default;
        ZAR_INLINE operator GLuint() const { return id; }
        ZAR_INLINE GLTexture(const char* path);

        ZAR_INLINE virtual void load(const char* path);
        ZAR_INLINE void generate(const char* path, const unsigned char* data);
        ZAR_INLINE void bind() const;
        ZAR_INLINE GLuint get_id() const;

    protected:
        GLint width = 0;
        GLint height = 0;
        GLuint id = 0;
        GLint channels = 0;

        GLuint internal_format = 0;
        GLuint image_format = 0;
        GLuint wrap_s = 0;
        GLuint wrap_t = 0;
        GLuint filter_min = 0;
        GLuint filter_max = 0;

        std::string name;
    };
}
