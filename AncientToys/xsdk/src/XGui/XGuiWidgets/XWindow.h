#pragma once
#include <Windows.h>

class XWindow
{
public:
    XWindow();
    ~XWindow();
    void show();

protected:
    virtual void win32OnCreate(long wParam, long lParam);
};

