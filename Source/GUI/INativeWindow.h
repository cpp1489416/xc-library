#pragma once

#include <Drawing2D/Drawing2D.h>
#include <GUI/GUI.h>

#include "../Core/Core.h"
#include "Events.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class IApplication;

    class INativeWindow
    {
    public:
        INativeWindow(IApplication * = nullptr) {}

    public:
        virtual void Show() = 0;

    protected:
        virtual void OnPaint(const PaintEvent& paintEvent) = 0;

        virtual void OnMouseDown(const MouseEvent& mouseEvent) = 0;
    };

} XC_END_NAMESPACE_2
