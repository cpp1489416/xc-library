#pragma once
#include "XCxcD3D11Drawer.h"

#pragma comment (lib, "Shcore.lib")

struct XCxcD3D11Window
{
public:

	XCxcD3D11Window();
	virtual ~XCxcD3D11Window();
	void show(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);

protected:
	virtual void initializeDrawer();
	virtual void messageLoop();
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	HWND hWnd;
	int height = 1000;
	int width = 1000;
	HINSTANCE hInstance;
	LPSTR lpCmdLine;
	int nCmdShow;
	XCxcD3D11Drawer *drawer;

	static XCxcD3D11Drawer *curDrawer;
};

