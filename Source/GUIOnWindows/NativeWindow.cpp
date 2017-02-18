#include "NativeWindow.h"

#include "Application.h"
#include <Windows.h>
#include <cassert>

XC_BEGIN_NAMESPACE_3(XC, GUI, Windows)
{
    class NativeWindow::IMPL
    {
    public:
        static LRESULT CALLBACK StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);

    public:
        LRESULT WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam);
        ATOM RegisterClassWin32();
        void CreateWindowWin32();
        void ShowWin32();

    public:
        Application * mApplication;
        WCHAR * mClassName = L"CXCNativeWindowClassName";
        HINSTANCE mHInstance;
        HWND mHWND;
    };

    LRESULT CALLBACK NativeWindow::IMPL::StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        IMPL * currentIMPL = (IMPL *)GetWindowLongPtr(hWND, GWLP_USERDATA);

        if (currentIMPL != nullptr)
        {
            return currentIMPL->WindowProcedureWin32(hWND, message, wParam, lParam);
        }
        else
        {
            if (message == WM_NCCREATE)
            {
                LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;

                IMPL * currentIMPL = (IMPL *)cs->lpCreateParams;
                currentIMPL->mHWND = hWND; // at this time, "CreateWindow" function is not returned
                
                SetWindowLongPtr(hWND, GWLP_USERDATA, (LONG)currentIMPL);
                return currentIMPL->WindowProcedureWin32(hWND, message, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hWND, message, wParam, lParam);  // there are functions before WM_NCCREATE
            }
        }
    }

    LRESULT NativeWindow::IMPL::WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        return DefWindowProc(hWND, message, wParam, lParam);
    }

    ATOM NativeWindow::IMPL::RegisterClassWin32()
    {
        mHInstance = GetModuleHandle(NULL);

        WNDCLASSEX wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);

        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = StaticWindowProcedureWin32;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = mHInstance;
        wcex.hIcon = NULL; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAINTEST));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = mClassName; // L"CXCNativeWindowClassName";
        wcex.hIconSm = NULL; // LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassEx(&wcex);
    }

    void NativeWindow::IMPL::CreateWindowWin32()
    {
        mHWND = CreateWindow(
            mClassName,
            L"CXC Window",
            WS_OVERLAPPEDWINDOW,
            100,
            0,
            100,
            100,
            nullptr,
            nullptr,
            mHInstance,
            (LPVOID)this);
    }

    void NativeWindow::IMPL::ShowWin32()
    {
        ShowWindow(mHWND, SW_MAXIMIZE);
    }

    NativeWindow::NativeWindow(Application * application) :
        INativeWindow(application)
    {
        mIMPL->mApplication = application;
        mIMPL->RegisterClassWin32();
        mIMPL->CreateWindowWin32();
    }

    NativeWindow::~NativeWindow()
    {
        XC_DELETE_IMPL(mIMPL);
    }

    void NativeWindow::Show()
    {
        mIMPL->ShowWin32();
    }

} XC_END_NAMESPACE_3

