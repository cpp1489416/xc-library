#include "XVirtualD3D11Window.h"

XVirtualD3D11Window::XVirtualD3D11Window()
{
}


XVirtualD3D11Window::~XVirtualD3D11Window()
{
}

void XVirtualD3D11Window::show(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	this->hInstance = hInstance;
	this->lpCmdLine = lpCmdLine;
	this->nCmdShow = nCmdShow;
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	LPCTSTR wndClassName = L"egjw";

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.lpszClassName = wndClassName;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wc);
	hWnd = CreateWindowEx(
		NULL,
		wndClassName,
		L"we",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	initializeDrawer();
	messageLoop();
}

void XVirtualD3D11Window::initializeDrawer()
{
}

void XVirtualD3D11Window::messageLoop()
{
}

