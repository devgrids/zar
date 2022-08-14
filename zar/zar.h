#pragma once

#ifndef ZAR_H
#define ZAR_H

#ifdef FX_PLATFORM_WINDOWS
    #ifdef FX_BUILD_DLL
        #define ZAR_API __declspec(dllexport)
    #else
        #define ZAR_API __declspec(dllimport)
    #endif // FX_BUILD_DLL
#else
    #error zar only support Windows!
#endif // FX_PLATFORM_WINDOWS

#ifdef FX_ENABLE_ASSERTS
    #define FX_ASSERT(x, ...) { if(!(x)) { FX_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define FX_ZAR_ASSERT(x, ...) { if(!(x)) { FX_ZAR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define FX_ASSERT(x, ...)
    #define FX_ZAR_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

namespace zar
{
    class Zar
    {
    public:
        Zar();
        explicit Zar(std::string name_class);
        std::string get_name() const;
        void show_class() const;
    private:
         std::string name_class;
    };
}
#endif

