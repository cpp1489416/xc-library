#pragma once
#include <Windows.h>
#include <ShellScalingApi.h>

#pragma comment (lib, "Shcore.lib")

class XVirtualD3D11Window
{
public:
	XVirtualD3D11Window();
	~XVirtualD3D11Window();
	void show(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);

protected:
	virtual void initializeDrawer();
	virtual void messageLoop();

	WNDPROC wndProc;
	HINSTANCE hInstance;
	LPSTR lpCmdLine;
	int nCmdShow;
	HWND hWnd;
	int width;
	int height;
};

