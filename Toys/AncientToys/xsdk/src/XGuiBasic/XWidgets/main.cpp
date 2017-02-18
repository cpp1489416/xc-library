#include "stdafx.h"
#include <Windows.h>
#include "XApplication.h"
#include "XWidget.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR rew, int nCmdShow)
{
    XApplication::setHInstance(hInstance);
    XWidget widget;
    widget.show();
    HBITMAP;
}