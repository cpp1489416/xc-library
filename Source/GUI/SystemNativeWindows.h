#pragma once

#include "NativeWindow.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Button : public NativeWindow
    {
    public:
        Button();

        void SetParent(NativeWindow& window) override;

    public:
        XC::Delegate<void> MClickedSignal;

    protected:

    private:
        LRESULT CALLBACK WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

        static LRESULT CALLBACK StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

        static WNDPROC sOriginalWindowProcedureWin32;
    };

} XC_END_NAMESPACE_2;