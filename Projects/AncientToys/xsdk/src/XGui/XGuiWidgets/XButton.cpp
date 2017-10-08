#include "stdafx.h"
#include "XButton.h"

XButton::XButton()
{

}

XButton::~XButton()
{
}

void XButton::win32OnCreate(HWND hWnd, long wParam, long lParam)
{
    XRectangle rect = getBoundary();
    hWnd = CreateWindow(
        L"Button", L"Click me!!!",
        WS_VISIBLE | BS_PUSHBUTTON | WS_CHILD,
        0,
        0,
        getBoundary().getWidth(),
        getBoundary().getHeight(), //rect.getHeight(),
        hWnd,
        NULL,
        xGetWindowInstance(),
        NULL
    );
}

void XButton::win32OnCommand(HWND hWnd, long wParam, long lParam)
{
    clickedSignal.emit();
}

void XButton::onSize(XSizeEvent * event)
{
    MoveWindow(hWnd, 0, 0, event->getWidth(), event->getHeight(), false);
}
