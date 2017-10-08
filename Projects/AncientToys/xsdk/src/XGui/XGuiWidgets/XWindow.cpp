#include "stdafx.h"
#include "XWindow.h"


XWindow::XWindow()
{
}

XWindow::~XWindow()
{
}

void XWindow::show()
{
    win32OnCreate(0, 0);
}

void XWindow::win32OnCreate(long wParam, long lParam)
{
}
