﻿#include "NativeWindow.h"


XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    HWND NativeWindow::GetWindowID()
    {
        return mHWND;
    }

    const Drawing2D::Rectangle& NativeWindow::GetBoundary()
    {
        return mBoundary;
    }

    void  NativeWindow::SetBoundary(const Drawing2D::Rectangle& boundary)
    {
        mBoundary = boundary;

        ::SetWindowPos(
            GetWindowID(),
            NULL,
            GetBoundary().RStart().RX(),
            GetBoundary().RStart().RY(),
            GetBoundary().RSize().RWidth(),
            GetBoundary().RSize().RHeight(),
            SWP_NOZORDER);
    }

    void NativeWindow::SetParent(NativeWindow& window)
    {
        ::SetParent(mHWND, window.mHWND);
    }

    void NativeWindow::SetText(const String& text)
    {
        ::SendMessage(mHWND, WM_SETTEXT, text.size(), (LPARAM)text.c_str());
    }


} XC_END_NAMESPACE_2;
