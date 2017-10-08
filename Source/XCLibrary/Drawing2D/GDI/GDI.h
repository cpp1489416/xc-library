#pragma once

#include <Windows.h>

#include "../Core.h"

XC_BEGIN_NAMESPACE_3(XC, Drawing2D, GDI)
{
    class PaintEngine : public IPaintEngine
    {
    public:
        HWND PrivateGetHWND()
        {
            return mHWND;
        }

        void PrivateSetHWND(HWND hWND)
        {
            mHWND = hWND;
        }

    private:
        HWND mHWND;
    };

    class Canvas : public ICanvas
    {
    public:
        Canvas();
        Canvas& operator=(const Canvas&) = delete;

    public:
        void Clear(const Color& color) override;

        void DrawRectangle(const Pen& pen, const Rectangle& rectangle) override;

        void DrawCircle(const Pen& pen, const Rectangle& area) override;

        void DrawLine(const Pen& pen, const Line& line) override;

        void BeginPaint(IPaintEngine& paintEngine) override;

        void EndPaint() override;

        void Translate(const Point& translation) override;

        void SetToIdentity() override;
    private:
        void SetPen(const Pen& pen);
        
        void DeletePen();
    private:
        HWND mHWND;
        HDC mHDC;
        HPEN mHPen;
        Point mTranslation;
    };

} XC_END_NAMESPACE_3;