#pragma once

namespace zar
{
    class __declspec(dllexport) Application
    {
    public:
        inline Application();
        inline ~Application();

    protected:
        bool bRun = true;
        float DeltaTime = 0.0f;
        float LastTime = 0.0f;
    };
}
