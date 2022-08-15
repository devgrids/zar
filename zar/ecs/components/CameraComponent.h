#pragma once
#include "../../api/opengl/GLCamera.h"
#include "../../core/interfaces/IComponent.h"

namespace zar
{
    class ZAR_API CameraComponent final : public IComponent
    {
    public:
        ZAR_INLINE CameraComponent() = default;
        ZAR_INLINE ~CameraComponent() override;
        ZAR_INLINE operator GLCamera*() const { return obj; }
        ZAR_INLINE operator GLCamera() const { return *obj; }
        ZAR_INLINE CameraComponent(const CameraComponent&) = default;
        ZAR_INLINE CameraComponent(GLCamera* camera);
        ZAR_INLINE CameraComponent(GLCamera camera);
 
        ZAR_INLINE void start() override;
        ZAR_INLINE void update() override;
    public:
        GLCamera* obj = nullptr;
    };
}
