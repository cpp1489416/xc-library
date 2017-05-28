#include "SystemNativeWindows.h"

#include "Application.h"

#include <cstdlib>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    WNDPROC Button::sOriginalWindowProcedureWin32;

    Button::Button()
    {
        mHWND = CreateWindow(
            L"Button",
            L"CXC Untitled button",
            BS_PUSHBUTTON,
            0,
            0,
            1000,
            1000,
            NULL,// parent.GetWindowID(),
            NULL,
            GetModuleHandle(NULL),
            NULL);

        if (mHWND == NULL)
        {
        }
        
        sOriginalWindowProcedureWin32 = (WNDPROC)::SetWindowLong(mHWND, GWL_WNDPROC, (LONG)StaticWindowProcedureWin32);
        SendMessage(GetWindowID(), WM_SETFONT, (WPARAM)Application::Win32GetBasicHFont(), 1);
        ::SetWindowLongPtr(mHWND, GWLP_USERDATA, (LONG)this);
    }

    void Button::SetParent(NativeWindow& window)
    {
        ::SetWindowLong(mHWND, GWL_STYLE, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON);
        ::SetParent(mHWND, window.GetWindowID());
    }

    LRESULT CALLBACK Button::StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        Button* current = (Button*)GetWindowLongPtr(hWND, GWLP_USERDATA);
        if (current == nullptr)
        {
            return (*sOriginalWindowProcedureWin32)(hWND, message, wParam, lParam);
        }
        else
        {
            return current->WindowProcedureWin32(hWND, message, wParam, lParam);
        }
    }

    LRESULT CALLBACK Button::WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_COMMAND:
            SetText(L"老子草泥马");
            break;
        case WM_LBUTTONDOWN:
            SetText(L"老子草泥马");
            MClickedSignal.Invoke();
            break;
        default:
            break;
        }

        return (*sOriginalWindowProcedureWin32)(hWND, message, wParam, lParam);
    }

} XC_END_NAMESPACE_2;

