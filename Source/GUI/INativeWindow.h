#pragma once

#include "../Core.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class INativeWindow
    {
    public:
        virtual void Show() = 0;
    };

} XC_END_NAMESPACE_2
