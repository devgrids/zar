#include "gl_texture.h"

zar::GLTexture::GLTexture(): width(0), height(0), internal_format(GL_RGB), image_format(GL_RGB), wrap_s(GL_REPEAT),
                             wrap_t(GL_REPEAT),
                             filter_min(GL_LINEAR), filter_max(GL_LINEAR)
{
}

zar::GLTexture::GLTexture(const char* path): width(0), height(0), internal_format(GL_RGB),
                                             image_format(GL_RGB), wrap_s(GL_REPEAT), wrap_t(GL_REPEAT),
                                             filter_min(GL_LINEAR), filter_max(GL_LINEAR)
{
}

void zar::GLTexture::load(const char* path)
{
}

void zar::GLTexture::generate(const char* path, const unsigned char* data)
{
    switch (channels)
    {
    case 1:
        internal_format = GL_RED;
        image_format = GL_RED;
        break;
    case 3:
        internal_format = GL_RGB;
        image_format = GL_RGB;
        break;
    case 4:
        internal_format = GL_RGBA;
        image_format = GL_RGBA;
        break;
    default: ;
    }

    name = path;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filter_max);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void zar::GLTexture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

GLuint zar::GLTexture::get_id() const
{
    return id;
}
