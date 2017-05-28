#pragma once

#include <Drawing2D/GDI/GDI.h>
#include <string>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    using PaintEngine = XC::Drawing2D::GDI::PaintEngine;
    using Canvas = XC::Drawing2D::GDI::Canvas;
    using String = std::wstring;

} XC_END_NAMESPACE_2
