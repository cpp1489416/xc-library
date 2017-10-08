#include "stdafx.h"
#include "XApplication.h"
#include <Windows.h>
#include <ShellScalingApi.h>

#pragma comment (lib, "Shcore.lib")

class XApplicationPrivate
{
public:
    void messageLoop();
};

XApplication::XApplication()
{
    m.reset(new XApplicationPrivate);
}


XApplication::~XApplication()
{
}


void XApplication::run()
{
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
   
    m->messageLoop();
}

void XApplicationPrivate::messageLoop()
{
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
