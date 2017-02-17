#pragma once

#include "../Core/Core.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class IApplication
    {
    public:
        virtual void Execute() = 0;
        virtual void Quit() = 0;
    };

} XC_END_NAMESPACE_2