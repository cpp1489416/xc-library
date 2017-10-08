#include "XCxcD3D11Window.h"
#include <functional>
#include <memory>
#include <ShellScalingApi.h>

using namespace std;

XCxcD3D11Drawer * XCxcD3D11Window::curDrawer = nullptr;

XCxcD3D11Window::XCxcD3D11Window()
{
	height = width = 1000;
	drawer = new XCxcD3D11Drawer;
	curDrawer = drawer;
}

XCxcD3D11Window::~XCxcD3D11Window()
{
	delete drawer;
}

void XCxcD3D11Window::initializeDrawer()
{
	drawer->setWidth(width);
	drawer->setHeight(height);
	drawer->setHWND(hWnd);
	drawer->initializeD3D11App();
	drawer->initializeScene();
}

void XCxcD3D11Window::messageLoop()
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
			curDrawer = drawer;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			//drawer->draw();
		}
	}
}

bool isOK = false;

LRESULT CALLBACK XCxcD3D11Window::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
    case WM_SIZE:
    {
        isOK = false;

        IDXGISwapChain *swapChain = curDrawer->getSwapChain();
        if (swapChain)
        {
            ID3D11Device *device = curDrawer->getDevice();
            ID3D11DeviceContext *context = curDrawer->getContext();
            ID3D11RenderTargetView *renderTargetView = curDrawer->getRenderTargetView();
            context->OMSetRenderTargets(0, 0, 0);

            // Release all outstanding references to the swap chain's buffers.
            renderTargetView->Release();

            HRESULT hr;
            // Preserve the existing buffer count and format.
            // Automatically choose the width and height to match the client rect for HWNDs.
            hr = swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

            // Perform error handling here!

            // Get buffer and create a render-target-view.
            ID3D11Texture2D* pBuffer;
            hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                (void**)&pBuffer);
            // Perform error handling here!

            hr = device->CreateRenderTargetView(pBuffer, NULL,
                &renderTargetView);
            // Perform error handling here!
            pBuffer->Release();

            context->OMSetRenderTargets(1, &renderTargetView, NULL);

            // Set up the viewport.
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            D3D11_VIEWPORT vp;
            vp.Width = width;
            vp.Height = height;
            vp.MinDepth = 0.0f;
            vp.MaxDepth = 1.0f;
            vp.TopLeftX = 0;
            vp.TopLeftY = 0;
            context->RSSetViewports(1, &vp);
            curDrawer->setWidth(width);
            curDrawer->setHeight(height);
        }

        if (curDrawer->getContext() != nullptr)
        {
            // curDrawer->draw();
        }

        isOK = true;
        break;
    }case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_LEFT:
		{
			curDrawer->rotateX(0.1f);
            curDrawer->draw();
			break;
		}
		case VK_RIGHT:
		{
			curDrawer->rotateY(0.1f);
			break;
		}
		case VK_DOWN:
		{
			curDrawer->rotateZ(0.1f);
			break;
		}
		default:
			break;
		}
        curDrawer->draw();
		break;
	}
    case WM_PAINT:
        if(isOK)
            curDrawer->draw();
        break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
		break;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


void XCxcD3D11Window::show(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
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
    initializeDrawer();
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	messageLoop();
}
