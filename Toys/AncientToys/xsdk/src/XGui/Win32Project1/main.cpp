#include "stdafx.h"
#include <Windows.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11sdklayers.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <d3d10.h>
#include "Window.h"
#include "DWindow.h"
#include <ShellScalingApi.h>
#include "DButton.h"

#pragma comment (lib, "Shcore.lib")

void messageLoop();


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    DButton widget;
    DWindow w;
    w.addWidget(&widget);
    w.show();
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

    messageLoop();
    return 0;
}
void messageLoop()
{
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        DispatchMessage(&msg);
        TranslateMessage(&msg);
    }
}