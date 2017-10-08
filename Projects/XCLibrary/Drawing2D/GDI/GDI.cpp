#include "GDI.h"

XC_BEGIN_NAMESPACE_3(XC, Drawing2D, GDI)
{
    Canvas::Canvas()
    {
       
    }

    void Canvas::Clear(const Color& color)
    {

    }

    void Canvas::DrawRectangle(const Pen& pen, const Rectangle& rectangle)
    {
        SetPen(pen);
        ::Rectangle(mHDC,
            rectangle.RStart().RX() + mTranslation.RX(),
            rectangle.RStart().RY() + mTranslation.RY(),
            rectangle.RStart().RX() + rectangle.RSize().RWidth() + mTranslation.RX(),
            rectangle.RStart().RY() + rectangle.RSize().RHeight() + mTranslation.RY());
    }

    void Canvas::DrawCircle(const Pen& pen, const Rectangle& area)
    {
        SetPen(pen);
        ::Ellipse(mHDC,
            area.RStart().RX() + mTranslation.RX(),
            area.RStart().RY() + mTranslation.RY(),
            area.RStart().RX() + area.RSize().RWidth() + mTranslation.RX(),
            area.RStart().RY() + area.RSize().RHeight() + mTranslation.RY());
    }

    void Canvas::DrawLine(const Pen& pen, const Line& line)
    {
        SetPen(pen);
        ::MoveToEx(mHDC, line.RFrom().RX() + mTranslation.RX(), line.RFrom().RY() + mTranslation.RY(), nullptr);
        ::LineTo(mHDC, line.RTo().RX() + mTranslation.RX(), line.RTo().RY() + mTranslation.RY());
    }

    void Canvas::BeginPaint(IPaintEngine& paintEngine)
    {
        PAINTSTRUCT ps;
        mHDC = ::BeginPaint((static_cast<PaintEngine&>(paintEngine)).PrivateGetHWND(), &ps);
    }

    void Canvas::EndPaint()
    {
        //DrawRectangle(Pen(Color(34, 0, 255), 3), Rectangle(Point(1, 100), Size(100, 500)));
        //DrawLine(Pen(), Line(Point(1, 100), Point(100, 500)));

        ::ReleaseDC(mHWND, mHDC);
    }

    void Canvas::Translate(const Point& translation)
    {
        mTranslation = translation;
    }

    void Canvas::SetToIdentity()
    {
        mTranslation = Point(0.0f, 0.0f);
    }

    void Canvas::SetPen(const Pen& pen)
    {
        mHPen = ::CreatePen(PS_SOLID, pen.RWidth(),
            RGB((int)pen.RColor().RRed(), (int)pen.RColor().RGreen(), (int)pen.RColor().RBlue()));
        ::DeleteObject(::SelectObject(mHDC, mHPen));
    }

    void Canvas::DeletePen()
    {

    }
} XC_END_NAMESPACE_3; 