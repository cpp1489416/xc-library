#include "stdafx.h"
#include "XWindowsDefines.h"
#include <Windows.h>

extern void xMain();

namespace
{
    HINSTANCE hInstance;
    int nCmdShow;
}

HINSTANCE xGetWindowInstance()
{
    return hInstance;
}

int xGetNCmdShow()
{
    return nCmdShow;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR rew, int nCmdShow)
{
    ::hInstance = hInstance;
    ::nCmdShow = nCmdShow;
    xMain();
    return 0;
}
