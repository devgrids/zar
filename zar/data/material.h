#pragma once

namespace zar
{
    struct Texture
    {
        GLuint id;
        std::string path;
    };

    struct Material
    {
        Texture diffuse_map;
        Texture specular_map;
        Texture normal_map;
        Texture height_map;
    };
}
