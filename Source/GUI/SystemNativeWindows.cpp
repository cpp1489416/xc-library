#include "SystemNativeWindows.h"

#include "Application.h"

#include <cstdlib>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    Button::Button()
    {
        mHWND = Application::GetDefaultHWND();
    }

    void Button::SetParent(NativeWindow& window)
    {
        if (mHWND != Application::GetDefaultHWND())
        {
            DestroyWindow(mHWND);
        }

        mHWND = CreateWindow(
            L"Button",
            L"CXC Untitled button",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            0,
            0,
            1000,
            1000,
            window.GetWindowID(),// parent.GetWindowID(),
            NULL,
            GetModuleHandle(NULL),
            NULL);

        SendMessage(GetWindowID(), WM_SETFONT, (WPARAM)Application::Win32GetBasicHFont(), 1);
        ::SetWindowLongPtr(mHWND, GWLP_USERDATA, (LONG)this);

        SetBoundary(GetBoundary());
    }

    void Button::Win32OnCommand(WPARAM wParam, LPARAM lParam)
    {
        switch (HIWORD(wParam))
        {
        case WM_NULL:
            MClickedSignal.Invoke();
            break;
        default:
            break;
        }
    }

    Label::Label()
    {
        mHWND = Application::GetDefaultHWND();
    }

    void Label::SetParent(NativeWindow& window)
    {
        if (mHWND != Application::GetDefaultHWND())
        {
            DestroyWindow(mHWND);
        }

        mHWND = CreateWindow(
            L"Static",
            L"CXC Untitled label",
            WS_VISIBLE | WS_CHILD | SS_CENTERIMAGE,
            0,
            0,
            1000,
            1000,
            window.GetWindowID(),// parent.GetWindowID(),
            NULL,
            GetModuleHandle(NULL),
            NULL);

        SendMessage(GetWindowID(), WM_SETFONT, (WPARAM)Application::Win32GetBasicHFont(), 1);
        ::SetWindowLongPtr(mHWND, GWLP_USERDATA, (LONG)this);
        SetBoundary(GetBoundary());
    }

    TextBox::TextBox()
    {
        mHWND = Application::GetDefaultHWND();
    }

    void TextBox::SetParent(NativeWindow& window)
    {
        if (mHWND != Application::GetDefaultHWND())
        {
            DestroyWindow(mHWND);
        }

        mHWND = CreateWindowEx(
            WS_EX_CLIENTEDGE | WS_EX_LEFT | WS_EX_LTRREADING | WS_EX_RIGHTSCROLLBAR,
            L"Edit",
            L"CXC Untitled label",
            WS_VISIBLE | WS_CHILD | ES_LEFT ,
            0,
            0,
            500,
            50,
            window.GetWindowID(),
            NULL,
            GetModuleHandle(NULL),
            NULL);

        SetWindowLongPtr(mHWND, GWLP_USERDATA, (LONG)this);
        SendMessage(GetWindowID(), WM_SETFONT, (WPARAM)Application::Win32GetBasicHFont(), 1);
        SetBoundary(GetBoundary());
    }

    void TextBox::Win32OnCommand(WPARAM wParam, LPARAM lParam)
    {
        switch (HIWORD(wParam))
        {
        case EN_CHANGE:
        {
            MTextChangedSignal.Invoke();
            break;
        }       
        default:
            break;
        }
        // SetText(L"egw");
        return;
    }


} XC_END_NAMESPACE_2;

