#pragma once
namespace zar
{
    class ZAR_API IComponent
    {
    public:
        ZAR_INLINE virtual ~IComponent() = default;
        ZAR_INLINE IComponent() = default;
        
        ZAR_INLINE virtual void start();
        ZAR_INLINE virtual void update();
    };
}
