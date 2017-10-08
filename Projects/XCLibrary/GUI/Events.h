#pragma once

#include <Core/Core.h>
#include <Drawing2D/Drawing2D.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class IEvent
    {

    };

    class BasicEvent : IEvent
    {

    };

    class PaintEvent : IEvent
    {
    public:
        PaintEvent(Drawing2D::ICanvas& canvas) : mCanvas(canvas)
        {
        }

        Drawing2D::ICanvas& RCanvas()
        {
            return mCanvas;
        }

    private:
        Drawing2D::ICanvas& mCanvas;

    };

    class MouseEvent : IEvent
    {
    };

} XC_END_NAMESPACE_2;