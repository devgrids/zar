#pragma once
namespace zar
{
    class ZAR_API GLCube
    {
    public:
        ZAR_INLINE GLCube();
        ZAR_INLINE GLCube(const GLCube&) = default;
        ZAR_INLINE ~GLCube();
        ZAR_INLINE void render() const;
    private:
        GLuint buffer_id = 0;
        GLuint vbo_id = 0;
    };

    ZAR_INLINE static void render_cube()
    {
        static GLCube cube;
        cube.render();
    }
}
