#include "Application.h"

#include <Windows.h>

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    extern void Main();

} XC_END_NAMESPACE_2

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class Application::IMPL
    {
    public:
        void InitializeWin32();
        void MessageLoopWin32();
        void QuitWin32();

    public:
        HINSTANCE mHInstance;
    };

    void Application::IMPL::InitializeWin32()
    {
        mHInstance = GetModuleHandle(NULL);
    }

    void Application::IMPL::MessageLoopWin32()
    {
        MSG msg;

        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Application::IMPL::QuitWin32()
    {
        PostQuitMessage(0);
    }

    Application::Application()
    {
        mIMPL->InitializeWin32();
    }

    Application::~Application()
    {
        XC_DELETE_IMPL(mIMPL)
    }

    void Application::Execute()
    {
        mIMPL->MessageLoopWin32();
    }

    void Application::Quit()
    {
        mIMPL->QuitWin32();
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