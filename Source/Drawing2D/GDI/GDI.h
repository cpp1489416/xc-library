#pragma once

#include <Windows.h>

#include "../Core.h"

XC_BEGIN_NAMESPACE_3(XC, Drawing2D, GDI)
{
    class Canvas : public ICanvas
    {
    public:
        void Clear(const Color& color) override;

        void DrawRectangle(const Pen& pen, const Rectangle& rectangle) override;

        void DrawCircle(const Pen& pen, const Rectangle& area) override;

        void DrawLine(const Pen& pen, const Line& line) override;
    };

} XC_END_NAMESPACE_3;