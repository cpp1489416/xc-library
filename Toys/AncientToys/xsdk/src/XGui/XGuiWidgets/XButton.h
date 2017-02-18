#pragma once
#include "XWidget.h"
#include <XSignal.h>

class XButton : public XWidget
{
public:
    XButton();
    ~XButton();
    XSignal clickedSignal;

protected:
    virtual void win32OnCreate(HWND hWnd, long wParam, long lParam);
    virtual void win32OnCommand(HWND hWnd, long wParam, long lParam);
    virtual void onSize(XSizeEvent *event);

private:
    HWND hWnd;
};