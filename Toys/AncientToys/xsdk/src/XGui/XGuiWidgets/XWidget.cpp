#include "stdafx.h"
#include "XWidget.h"
#include <Windows.h>
#include "XWindowsDefines.h"
#include <XRectangle.h>
#include <string>
#include <XVector.h>
#include <d2d1.h>
#include <vector>

LPCTSTR XWidget::wndClassName = L"XWINDOWBYCXC";
int XWidget::countWindows = 0;

void XWidget::subInitialize()
{
    hWnd = CreateWindowEx(
        NULL,
        XWidget::wndClassName,
        title,
        parent == nullptr ? WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN : WS_VISIBLE | WS_CHILDWINDOW | WS_CLIPSIBLINGS,
        (int)boundary.getX(),
        (int)boundary.getY(),
        (int)boundary.getWidth(),
        (int)boundary.getHeight(),
        parent == nullptr ? NULL : parent->hWnd,
        NULL,
        xGetWindowInstance(),
        this
    );

    for (int i = 0; i < childs.size(); i++)
    {
        childs[i]->subInitialize();
    }
}

void XWidget::win32CreateClass()
{
    WNDCLASSEX wndClass;
    ZeroMemory(&wndClass, sizeof(wndClass));
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = NULL,// CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = XWidget::staticWindowProcess;
    wndClass.lpszClassName = XWidget::wndClassName;
    wndClass.hInstance = xGetWindowInstance();
    wndClass.lpszMenuName = NULL;
    wndClass.cbClsExtra = NULL;
    wndClass.cbWndExtra = NULL;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hbrBackground = NULL, //(HBRUSH)(COLOR_WINDOW);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClassEx(&wndClass);
}

LRESULT CALLBACK XWidget::staticWindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (LONG_PTR userData = GetWindowLongPtr(hWnd, GWLP_USERDATA))
    {
        XWidget * curWindow = reinterpret_cast<XWidget *>(userData);
        return curWindow->windowProcess(hWnd, msg, wParam, lParam);
    }

    if (msg == WM_NCCREATE)
    {
        LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
        XWidget *curWindow = (XWidget *)createStruct->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)curWindow);
        return curWindow->windowProcess(hWnd, msg, wParam, lParam);
    }
}

LRESULT XWidget::windowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
    {
        countWindows--;
        PostQuitMessage(0);
        break;
    }
    case WM_PAINT:
    {
        onPaint(&paintEvent);
        //return 0;
        break;
    }
    case WM_SIZE:
    {
        sizeEvent = XSizeEvent(LOWORD(lParam), HIWORD(lParam));
        onSize(&sizeEvent);
        break;
    }
    case WM_MOUSEMOVE:
    {
        sizeEvent = XSizeEvent(LOWORD(lParam), HIWORD(lParam));
        onMouseMove(&sizeEvent);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        break;
    }
    case WM_COMMAND:
    {
        XWidget *me = (XWidget *)GetWindowLongPtr((HWND)lParam, GWL_USERDATA);
        win32OnCommand(hWnd, (long)wParam, (long)lParam);
        break;
    } 
    case WM_CREATE:
    {
        //for (int i = 0; i < 19; i++)
        //{
        //    for (int j = 0; j < 19; j++)
        //    {
        //        XRectangle rect = getBoundary();
        //        HWND hwnd = CreateWindow(
        //            L"Button", L"Click me!!!",
        //            WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD,
        //            i* 50,
        //            j * 50,
        //            50,
        //            50, //rect.getHeight(),
        //            hWnd,
        //            NULL,
        //            xGetWindowInstance(),
        //            NULL
        //        );
        //    }
        //}
        win32OnCreate(hWnd, (long)wParam, (long)lParam);
        break;
    }
    default:
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

XWidget::XWidget()
{
    boundary = XRectangle(100, 100, 1000, 500);
    title = L"CXC is genius";
    parent = nullptr;
    win32CreateClass();
}

XWidget::~XWidget()
{
}

void XWidget::show(XWidget *parent)
{    
    subInitialize();
    ShowWindow(hWnd, xGetNCmdShow());
}

void XWidget::setBoundary(const XRectangle & rectangle)
{
    boundary = rectangle;
    MoveWindow(hWnd, boundary.getX(), boundary.getY(), boundary.getWidth(), boundary.getHeight(), true);
    SetWindowText(hWnd, L"¸öjoeete ");
}

XRectangle XWidget::getBoundary() const
{
    return boundary;
}

void XWidget::addWidget(XWidget * widget)
{
    childs.push_back(widget);
    widget->parent = this;
}

XWidget * XWidget::getParent() const
{
    return parent;
}

HWND XWidget::win32GetHwnd() const
{
    return hWnd;
}

void XWidget::onKeyPressed()
{
}

void XWidget::onPaint(XPaintEvent * event)
{
}

void XWidget::onSize(XSizeEvent * event)
{
}

void XWidget::onMouseMove(XMouseEvent * event)
{
}

void XWidget::win32OnCreate(HWND hWnd, long wParam, long lParam)
{
    MessageBox(hWnd, L"ekthetiu", L"gerjhy8", MB_OK);
}

void XWidget::win32OnCommand(HWND hWnd, long wParam, long lParam)
{
}
