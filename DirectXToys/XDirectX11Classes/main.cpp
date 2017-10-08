
#include <Windows.h>
#include <ShellScalingApi.h>

#pragma comment (lib, "Shcore.lib")

HWND hWnd;
int width = 1000;
int height = 1000;
//XCxcD3D11Drawer d3dApp;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void initializeWindow(HINSTANCE hInstance, int nCmdShow);
void messageLoop();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	initializeWindow(hInstance, nCmdShow);
//	d3dApp.setHeight(height);
//	d3dApp.setWidth(width);
//	d3dApp.setHWND(hWnd);
//	d3dApp.initializeD3D11App();
//	d3dApp.initializeScene();
	messageLoop();
	return 0;
}

void initializeWindow(HINSTANCE hInstance, int nCmdShow)
{
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	LPCTSTR wndClassName = L"egjw";

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
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

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
			//d3dApp.rotateY(0.05f);
			break;
		}
		case VK_RIGHT:
		{
			//d3dApp.rotateX(0.05f);
			break;
		}
		case VK_DOWN:
		{
			//d3dApp.rotateZ(0.05f);
			break;
		}
		default:
			break;
		}
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void messageLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//d3dApp.update();
		//	d3dApp.draw();
		}
	}
}