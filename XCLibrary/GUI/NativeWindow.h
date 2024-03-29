#pragma once

#include <Windows.h>
#include <Core/Core.h>
#include <Drawing2D/Drawing2D.h>
#include <Drawing2D/GDI/GDI.h>
#include "Defines.h"
#include "Application.h"
#include "Events.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class NativeWindow : public CallableObject
    {
    public:
        NativeWindow();

        ~NativeWindow();

    public:
        HWND GetWindowID();

        const Drawing2D::Rectangle& GetBoundary();

        void SetBoundary(const Drawing2D::Rectangle& boundary);
      
        const String& GetText();

        void SetText(const String& text);

        const Drawing2D::Size& GetMinimumSize();

        void SetMinimumSize(const Drawing2D::Size& size);

        bool IsSizeAutoChangeable();

        void SetSizeAutoChangeable(bool value);

    public:
        virtual void SetParent(NativeWindow& window);

        virtual void OnSizeChanged(BasicEvent* event);

        virtual void Win32OnCommand(WPARAM wParam, LPARAM lParam);

    protected:
        HWND mHWND = NULL;

        Drawing2D::Rectangle mBoundary;

    private:
        Drawing2D::Size mMinimumSize = Drawing2D::Size(-1.0, -1.0);
        bool mIsSizeAutoChangeable;
    };

} XC_END_NAMESPACE_2;