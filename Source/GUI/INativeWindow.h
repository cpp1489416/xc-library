#pragma once

#include "../Core/Core.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class IApplication;

    class INativeWindow
    {
    public:
        INativeWindow(IApplication * = nullptr) {}

    public:
        virtual void Show() = 0;
    };

} XC_END_NAMESPACE_2
