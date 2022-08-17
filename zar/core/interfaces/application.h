#pragma once

#ifndef I_APPLICATION_H
#define I_APPLICATION_H

namespace zar
{
    class ZAR_API IApplication
    {
    public:
        virtual ~IApplication();
        IApplication() = default;

        inline virtual void start() = 0;
        inline virtual void update() = 0;
        inline virtual void render() = 0;

        int width{};
        int height{};
    };
}
#endif
