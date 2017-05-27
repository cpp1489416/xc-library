#include "Widget.h"

#include <Windows.h>
#include <cassert>
#include <Drawing2D/GDI/GDI.h>
#include "Application.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    const Drawing2D::Rectangle& Widget::GetBoundary()
    {
        return mBoundary;
    }

    void Widget::SetBoundary(const Drawing2D::Rectangle& boundary)
    {
        mBoundary = boundary;
        if (mParent != nullptr) // not the top window
        {
            for (auto child : mChildWidgets)
            {
                child->SetBoundary(child->GetBoundary());
            }

            Repaint();
        }
        else
        {
            return;
        }
    }

    LRESULT CALLBACK Widget::StaticWindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        Widget* currentIMPL = (Widget*)GetWindowLongPtr(hWND, GWLP_USERDATA);

        if (currentIMPL != nullptr)
        {
            return currentIMPL->WindowProcedureWin32(hWND, message, wParam, lParam);
        }
        else
        {
            if (message == WM_NCCREATE)
            {
                LPCREATESTRUCT cs = (LPCREATESTRUCT)lParam;

                Widget* currentIMPL = (Widget*)cs->lpCreateParams;
                currentIMPL->mHWND = hWND; // at this time, "CreateWindow" function is not returned

                SetWindowLongPtr(hWND, GWLP_USERDATA, (LONG_PTR)currentIMPL);
                return currentIMPL->WindowProcedureWin32(hWND, message, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hWND, message, wParam, lParam);  // there are functions before WM_NCCREATE
            }
        }
    }

    LRESULT Widget::WindowProcedureWin32(HWND hWND, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE:
            break;
        case WM_DESTROY:
        {
            mApplication->Quit();
            break;
        }
        case WM_PAINT:
        {
            mCanvas.BeginPaint(*(this));
            OnPaint(PaintEvent(mCanvas));
            mCanvas.EndPaint();
            break;
        }
        case WM_LBUTTONDOWN:
            OnMouseDown(MouseEvent());
            break;
        case WM_RBUTTONDOWN:

            break;
        default:
            break;
        }

        return DefWindowProc(hWND, message, wParam, lParam);
    }

    ATOM Widget::RegisterClassWin32()
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
        wcex.lpszClassName = mClassName; // L"CXCWidgetClassName";
        wcex.hIconSm = NULL; // LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassEx(&wcex);
    }

    void Widget::CreateWindowWin32()
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
        
        PrivateSetHWND(mHWND);
    }

    void Widget::ShowWin32()
    {
        RegisterClassWin32();
        CreateWindowWin32();
        ShowWindow(mHWND, SW_MAXIMIZE);
    }

    Widget::Widget(Application * application)
    {
        mApplication = application;
    }

    Widget::~Widget()
    {
    }

    void Widget::OnCreate(BasicEvent& event)
    {

    }

    void Widget::OnResize(BasicEvent& event)
    {
    }

    void Widget::OnPaint(PaintEvent& paintEvent)
    {
    }

    void Widget::OnMouseDown(MouseEvent& mouseEvent)
    {
    }

    void Widget::Show()
    {
        ShowWin32();
    }

    void Widget::Repaint()
    {
        OnPaint(PaintEvent(mCanvas));
        for (auto widget : mChildWidgets)
        {
            widget->Repaint();
        }
    }
    
} XC_END_NAMESPACE_2;

