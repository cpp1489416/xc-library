#include <XVirtualD3D11Drawer.h>
#include "XCxcD3D11Drawer.h"
#include <Windows.h>
#include <ShellScalingApi.h>
#include "XCxcD3D11Window.h"

#pragma comment (lib, "XDirectX11Classes.lib")
#pragma comment (lib, "XD3D11Shapes.lib")
#pragma comment (lib, "Shcore.lib")

HINSTANCE hInstance;
LPSTR lpCmdLine;
int nCmdShow;

DWORD WINAPI ThreadProc1(LPVOID lpParam)
{
	XCxcD3D11Window w;
	w.show(hInstance, lpCmdLine, nCmdShow);
	//	printf("sub thread started\n");
	//	printf("sub thread finished\n");
	return 0;
}

DWORD WINAPI ThreadProc2(LPVOID lpParam)
{
	XCxcD3D11Window w;
	w.show(hInstance, lpCmdLine, nCmdShow);
	//	printf("sub thread started\n");
	//	printf("sub thread finished\n");
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

int ymain(int argc, char ** argv);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	::hInstance = hInstance;
	::lpCmdLine = lpCmdLine;
	::nCmdShow = nCmdShow;
	DWORD threadID;
	HANDLE hThread;
//	hThread = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &threadID); // 创建线程
	//hThread = CreateThread(NULL, 0, ThreadProc2, NULL, 0, &threadID); // 创建线程
	XCxcD3D11Window w;
    w.show(hInstance, lpCmdLine, nCmdShow);
	ymain(0, nullptr);
	return 0;
}

int ymain(int argc, char ** argv)
{
	return 0;
}

