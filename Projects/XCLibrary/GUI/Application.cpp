#include "Application.h"

#include <Windows.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    extern void Main();

} XC_END_NAMESPACE_2

XC_BEGIN_NAMESPACE_2(XC, GUI)
{

    void Application::InitializeWin32()
    {
        mHInstance = GetModuleHandle(NULL);
    }

    void Application::MessageLoopWin32()
    {
        MSG msg;

        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Application::QuitWin32()
    {
        PostQuitMessage(0);
    }

    Application::Application()
    {
        InitializeWin32();
    }

    Application::~Application()
    {
    }

    void Application::Execute()
    {
        MessageLoopWin32();
    }

    void Application::Quit()
    {
        QuitWin32();
    }

    HWND Application::GetDefaultHWND()
    {
        static bool isCreated = false;
        static HWND hWnd = NULL;
        if (isCreated == false)
        {
            isCreated = true;
            hWnd = CreateWindow(
                L"Button",
                L"CXC Untitled button",
                NULL,
                0,
                0,
                1000,
                1000,
                NULL,// parent.GetWindowID(),
                NULL,
                GetModuleHandle(NULL),
                NULL);
            
        }

        return hWnd;
    }

    HFONT Application::Win32GetBasicHFont()
    {
        static HFONT hFont;
        bool isDone = false;
        if (!isDone)
        {
            LOGFONT logFont;
            SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &logFont, 0);
            hFont = CreateFontIndirect(&logFont);
            isDone = true;
        }

        return hFont;

    }

} XC_END_NAMESPACE_2;

int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdLine)
{
    XC::GUI::Main();
}