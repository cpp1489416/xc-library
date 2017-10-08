#pragma once

#include <Windows.h>
#include <Core/Core.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Application
    {
    public:
        static  HWND GetDefaultHWND();

    public:
        Application();

        ~Application();

    public:
        static HFONT Win32GetBasicHFont();

        void Execute();

        void Quit();

    private:
        void InitializeWin32();

        void MessageLoopWin32();

        void QuitWin32();

    private:
        HINSTANCE mHInstance;
    };

} XC_END_NAMESPACE_2;