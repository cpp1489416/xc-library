#include  "UserNativeWindow.h"

#include <Windows.h>
#include <cassert>
#include <Drawing2D/GDI/GDI.h>
#include "Application.h"
#include "Layout.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    LRESULT CALLBACK UserNativeWindow::StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        UserNativeWindow* current = (UserNativeWindow*)GetWindowLongPtr(hWND, GWLP_USERDATA);

        if (current != nullptr)
        {
            return current->WindowProcedureWin32(hWND, message, wParam, lParam);
        }
        else
        {
            if (message == WM_NCCREATE)
            {
                LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;

                UserNativeWindow* current = (UserNativeWindow*)cs->lpCreateParams;
                current->mHWND = hWND; // at this time, "CreateWindow" function is not returned

                SetWindowLongPtr(hWND, GWLP_USERDATA, (LONG_PTR)current);
                return current->WindowProcedureWin32(hWND, message, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hWND, message, wParam, lParam);  // there are functions before WM_NCCREATE
            }
        }
    }

    LRESULT UserNativeWindow::WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:
        {
            break;
        }
        case WM_DESTROY:
        {
            mApplication->Quit();
            break;
        }
        case WM_PAINT:
        {
            break;
        }
        case WM_LBUTTONDOWN:
        {
            break;
        }
        case WM_SIZE:
        {
            RECT rect;
            GetClientRect(mHWND, &rect);
        
            mBoundary = Drawing2D::Rectangle(
                Drawing2D::Point(rect.left, rect.top),
                Drawing2D::Size(rect.right - rect.left, rect.bottom - rect.top)
            );

            if (mLayout != nullptr)
            {
                mLayout->Resize(Drawing2D::Rectangle(Drawing2D::Point(0, 0), GetBoundary().RSize()));
            }

            break;
        }
        case WM_COMMAND:
        {
            HWND hWnd = (HWND)lParam;
            if (hWnd == NULL)
            {
                break;
            }

            NativeWindow* window = (NativeWindow*)::GetWindowLongPtr(hWnd, GWLP_USERDATA);
            if (window != nullptr)
            {
                window->Win32OnCommand(wParam, lParam);
            }
            break;
        }
        default:
            break;
        }

        return DefWindowProc(hWND, message, wParam, lParam);
    }

    ATOM UserNativeWindow::RegisterClassWin32()
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
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
        wcex.lpszMenuName = NULL;
        wcex.lpszClassName = mClassName; // L"CXCUserNativeWindowClassName";
        wcex.hIconSm = NULL; // LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassEx(&wcex);
    }

    void UserNativeWindow::CreateWindowWin32()
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

    void UserNativeWindow::ShowWin32()
    {
        ShowWindow(mHWND, SW_MAXIMIZE);
    }

    UserNativeWindow::UserNativeWindow(Application * application)
    {
        RegisterClassWin32();
        CreateWindowWin32();
        mApplication = application;
    }

    UserNativeWindow::~UserNativeWindow()
    {
    }

    void UserNativeWindow::Show()
    {
        ShowWin32();
    }

    UserNativeWindow* UserNativeWindow::GetParent()
    {
        return mParent;
    }

    void UserNativeWindow::AddUserNativeWindow(NativeWindow& widget)
    {
        //        mChildUserNativeWindows.PushBack(&widget);

        ::SetParent(widget.GetWindowID(), GetWindowID());
        ::SetWindowLong(widget.GetWindowID(), GWL_HWNDPARENT, (LONG)GetWindowID());
        widget.SetBoundary(widget.GetBoundary());
        widget.SetParent(*this);
    }

    void UserNativeWindow::SetLayout(Layout* layout)
    {
        mLayout = layout;
        if (mLayout != nullptr)
        {
            layout->SetParent(*this);
            for (NativeWindow* window : mLayout->GetWindows())
            {
                window->SetParent(*this);
            }
        }
    }



} XC_END_NAMESPACE_2;

