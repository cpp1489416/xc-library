#include "stdafx.h"
#include "Window.h"
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "XBasic.h"
#include <windowsx.h>
#include <XRectangle.h>
#include <d2d1.h>
#include <cmath>

using namespace std;

#define d3d11DevCon context
#define d3d11Device device
#define SwapChain swapChain
#define World world

Window *curWindow;

int mouseX;
int mouseY;
bool isDown = false;

void Window::show()
{
    curWindow = this;
    width = 1000;
    height = 1000;
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style =NULL,// CS_HREDRAW;// | CS_VREDRAW;
    wc.lpfnWndProc = Window::xwndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_ASTERISK);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL; // (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = Window::className;
    wc.hIconSm = LoadIcon(NULL, IDI_ERROR);

  
    RegisterClassEx(&wc);
    hWnd = CreateWindowEx(
        NULL,
        Window::className,
        L"gfdjlksit健康然后逛街如何个",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
        NULL,
        NULL,
        hInstance,
        this
    );

    initializeD3D();
    ShowWindow(hWnd, nCmdShow);
}

LRESULT Window::xwndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
        void *lpCreateParam = createStruct->lpCreateParams;
        Window * thisWindow = (Window *)lpCreateParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)thisWindow);
        return thisWindow->wndProc(hWnd, msg, wParam, lParam);
    }
    else
    {
        Window * w = (Window *)GetWindowLongPtr(hWnd, GWL_USERDATA);
        return w->wndProc(hWnd, msg, wParam, lParam);
    }
}

LRESULT Window::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_MOUSEMOVE:
        mouseX = GET_X_LPARAM(lParam);
        mouseY = GET_Y_LPARAM(lParam);
        D3DRender();
        break;
    case WM_LBUTTONDOWN:
        isDown = true;
        D3DRender();
        break;
    case WM_LBUTTONUP:
        isDown = false;
        D3DRender();
    case WM_CREATE:
        D3DRender();
        break;
    case WM_NCCREATE:
        D3DRender();
        break;
    case WM_SETFOCUS:
        D3DRender();
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
      //  break;
        width = LOWORD(lParam);
        height = HIWORD(lParam);
        D3DSizeChanged();
        D3DRender();
    case WM_PAINT:
        D3DRender();
        break;
    default:
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Window::initializeD3D()
{
    numElements = 2;
    xBasicInitializeDirectX11(hWnd, &SwapChain, &device, &context, &renderTargetView);

    xBasicCreateShader(device, context, L"Effects.fx", &VS_Buffer, &PS_Buffer, &VS, &PS);

    //Create the vertex buffer
    Vertex v[100] =
    {
        Vertex(10.f, 10.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(100.f,  10.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(100.f,  100.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(10.f, 100.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(10.f, 10.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),

        Vertex(10.f, 10.f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
        Vertex(100.f, 10.f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
        Vertex(100.f, 100.f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
        Vertex(10.f, 100.f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
        Vertex(10.f, 10.f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f),

        Vertex(10.f, 10.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
        Vertex(100.f,  10.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
        Vertex(100.f,  100.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
        Vertex(10.f, 100.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
        Vertex(10.f, 10.f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
    };

    float pi = 3.14;
    for (int i = 0; i < 100; i++)
    {
        v[i] = Vertex(cos(i * 2 * pi / 100) * 50, sin(i * 2 * pi / 100) * 50, 0, 1, 1, 1, 1);
    }

    DWORD indices[] =
    {
        0, 1, 2,
        0, 2, 3,
    };


    xBasicCreateBuffer(device,
        D3D11_BIND_INDEX_BUFFER,
        sizeof(DWORD) * 2 * 3,
        indices,
        &squareIndexBuffer
    );
    d3d11DevCon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    xBasicCreateBuffer(device,
        D3D11_BIND_VERTEX_BUFFER,
        sizeof(Vertex) * 150,
        v,
        &squareVertBuffer
    );

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    d3d11DevCon->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);

    //Create the Input Layout
    d3d11Device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
        VS_Buffer->GetBufferSize(), &vertLayout);

    //Set the Input Layout
    d3d11DevCon->IASetInputLayout(vertLayout);

    //Set Primitive Topology
    d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

   

    xBasicCreateBuffer(
        device,
        D3D11_BIND_CONSTANT_BUFFER,
        sizeof(cbPerObject),
        &cbPerObj,
        &cbPerObjectBuffer
    );

    XMStoreFloat4(&camPosition, XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f));
    XMStoreFloat4(&camTarget, XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f));
    XMStoreFloat4(&camUp, XMVectorSet(0.0f, 1.f, 0.0f, 0.0f));

    XMStoreFloat4x4(
        &camView,
        XMMatrixLookAtLH(
            XMLoadFloat4(&camPosition),
            XMLoadFloat4(&camTarget),
            XMLoadFloat4(&camUp)
        )
    );

    XMStoreFloat4x4(
        &camProjection,
        XMMatrixOrthographicOffCenterLH(10, 50, 10, 100, -1, 100)
        // XMMatrixOrthographicLH(width, height, 0.1, 100000000)
    );

}

void Window::D3DSizeChanged()
{
    if (width == 0 || height == 0)
    {
        return;
    }

    xBasicChangeSize(device, context, swapChain, &renderTargetView, width, height);

    //XMStoreFloat4x4(
    //    &camView,
    //    XMMatrixIdentity()
    //);
   
    XMStoreFloat4x4(
        &camProjection,
        // XMMatrixOrthographicOffCenterLH(10, width, height, 10, 0.1, 100.f)
        XMMatrixOrthographicLH(width, height, 0.1, 1000)
    );

    XMMATRIX tmpWorld = XMMatrixIdentity();
    tmpWorld *= XMMatrixTranslation(-width / 2, -height / 2, 0);
    tmpWorld *= XMMatrixScaling(1, 1, 0);
    XMStoreFloat4x4(&world, tmpWorld);
}

void Window::D3DRender()
{
    if (!d3d11DevCon)
    {
        return;
    }

    FLOAT bgColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, bgColor);

    XMMATRIX tmpWord = XMLoadFloat4x4(&world);
    XMMATRIX tmpView = XMLoadFloat4x4(&camView);
    XMMATRIX tmpProjection = XMLoadFloat4x4(&camProjection);

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            XMMATRIX tmpWord = XMLoadFloat4x4(&world);
            tmpWord *= XMMatrixTranslation(10 * i, 10 * j, 0);
            XMStoreFloat4x4(
                &WVP,
                tmpWord *
                tmpView *
                tmpProjection
            );

            XMStoreFloat4x4(
                &cbPerObj.WVP,
                XMMatrixTranspose(XMLoadFloat4x4(&WVP))
            );

            d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);

            d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);

          //  XRectangle rect(10, 10, 100 - 10, 100 - 10);
           // if (rect.isInMe(XPoint(mouseX, mouseY)))
           // {
                if (!isDown)
                {
                    context->Draw(5, 5);
                }
                else
                {
                    context->Draw(5, 10);
                }
           // }
          //  else
          //  {
           //     context->Draw(5, 0);
            //}
        }
        context->OMSetRenderTargets(1, &renderTargetView, NULL);
    }
 
    SwapChain->Present(0, 0);
}
