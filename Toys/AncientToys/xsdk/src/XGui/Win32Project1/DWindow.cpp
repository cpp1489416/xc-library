#include "stdafx.h"
#include "DWindow.h"
#include "XBasic.h"
#include <cstdlib>
#include <ctime>

using namespace std;

ID3D11Buffer *squareIndexBuffer;
ID3D11Buffer *squareVertBuffer;

DWindow *DWindow::self;

DWindow::DWindow()
{
    self = this;
}

DWindow::~DWindow()
{
}

void DWindow::show()
{
    registerClass();
    initializeDirectX();
    widget->onCreate();

    ::ShowWindow(hwnd, SW_MAXIMIZE);
}

void DWindow::addWidget(DWidget * widget)
{
    this->widget = widget;
    widget->window = this;
}

void DWindow::updateConstantBuffer()
{
}

void DWindow::rotateX()
{
}

void DWindow::rotateY()
{
}

void DWindow::rotateZ()
{
}

LRESULT CALLBACK DWindow::staticWindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return self->windowProcess(hwnd, msg, wParam, lParam);
}

LRESULT DWindow::windowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{  
    HWND tBox = 0;
    switch (msg)
    {
    case WM_PAINT:
    {
        InvalidateRect(tBox, NULL, true);
        UpdateWindow(tBox);
        onPaint(&paintEvent);
     //   SendMessage(tBox, WM_PAINT, 0, 0);
        // UpdateWindow(tBox);
        
        //RedrawWindow(tBox, , NULL, RDW_VALIDATE);
        break;
    }
    case WM_SIZE:
    {/*
        InvalidateRect(tBox, NULL, true);
        UpdateWindow(tBox);*/
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        sizeEvent.width = width;
        sizeEvent.height = height;
        onSize(&sizeEvent);
        widget->onSize(&sizeEvent);    
        
        break;
    }
    case WM_LBUTTONDOWN:
    {
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        mouseEvent.width = x;
        mouseEvent.height = y;
        onMouseDown(&mouseEvent);
       break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        onDestory();
        break;
    }
    case WM_CREATE:
    {
        tBox = CreateWindow(L"edit", L"grege", WS_VISIBLE | WS_CHILD, 100, 100, 100, 100, hwnd, NULL, GetModuleHandle(NULL), NULL);
      //  widget->onCreate();
        break;
    }
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void DWindow::onSize(XSizeEvent * event)
{
    if (event->width == 0 || event->height == 0)
    {
        return;
    }

    ::xBasicChangeSize(device, context, swapChain, &renderTargetView, event->width, event->height);

    XMMATRIX tmpWorld = XMMatrixIdentity();
    tmpWorld *= XMMatrixTranslation(-event->width / 2, -event->height / 2, 0);
    tmpWorld *= XMMatrixScaling(1, 1, 0);
    XMStoreFloat4x4(&world, tmpWorld);

    XMMATRIX tmpProjection = XMMatrixOrthographicLH(event->width, -event->height, 0.1, 100);
    XMStoreFloat4x4(&projection, tmpProjection);

    onPaint(&paintEvent);
}

void DWindow::onPaint(XPaintEvent * event)
{
    XMMATRIX wvp;

    FLOAT bgColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    context->ClearRenderTargetView(renderTargetView, bgColor);

 //   XMMATRIX tmpWord = XMLoadFloat4x4(&world);
    XMMATRIX tmpView = XMLoadFloat4x4(&view);
    XMMATRIX tmpProjection = XMLoadFloat4x4(&projection);

    //for (int i = 0; i < 100; i++)
    //{
    //    for (int j = 0; j < 100; j++)
    //    {
    //        if (rand() % 2)
    //        {
    //            continue;
    //        }

    XMMATRIX tmpWord = XMLoadFloat4x4(&world);
    tmpWord *= XMMatrixTranslation(100 * 0, 100 * 0, 0);
    XMStoreFloat4x4(&WVP.world, XMMatrixTranspose(tmpWord));
    XMStoreFloat4x4(&WVP.view, XMMatrixTranspose(tmpView));
    XMStoreFloat4x4(&WVP.projection, XMMatrixTranspose(tmpProjection));
    updateWVP();
  /*          }
    }*/
    widget->onPaint(event);
    swapChain->Present(0, 0);
}

void DWindow::onMouseDown(XMouseEvent * event)
{
    widget->onMouseDown(event);
}

void DWindow::onMouseMove(XMouseEvent * event)
{
}

void DWindow::onDestory()
{
}

void DWindow::updateWVP()
{
    context->UpdateSubresource(constantBuffer, 0, NULL, &WVP, 0, 0);

    context->VSSetConstantBuffers(0, 1, &constantBuffer);
}

void DWindow::registerClass()
{
    LPWSTR name = L"ttttttt";

    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = name;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = DWindow::staticWindowProcess;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;
    wc.style = NULL; // CS_HREDRA         W;// | CS_VREDRAW;
    wc.hbrBackground = NULL; // (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName = NULL;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wc);

    hwnd = CreateWindow(
        name,
        L"看过后二化工",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        900,
        900,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );
}

void DWindow::initializeDirectX()
{
    ::xBasicInitializeDirectX11(hwnd, &swapChain, &device, &context, &renderTargetView);
    ::xBasicCreateShader(device, context, L"Effects.fx", &VS_Buffer, &PS_Buffer, &VS, &PS);
    ::xBasicCreateBuffer(device, D3D11_BIND_CONSTANT_BUFFER, sizeof(CPerObject), &WVP, &constantBuffer);

    XMVECTOR eye = XMVectorSet(0.0f, 0.0f, -1.5f, 0.0f);
    XMVECTOR target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    XMMATRIX tmpView = XMMatrixLookAtLH(eye, target, up);
    XMStoreFloat4x4(&view, tmpView);


    //Create the Input Layout
    device->CreateInputLayout(layout, 2, VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), &vertexLayout);

    //Set the Input Layout
    context->IASetInputLayout(vertexLayout);

    //Set Primitive Topology
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    Vertex v[100] =
    {
        Vertex(10.f, 10.f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
        Vertex(100.f,  10.f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
        Vertex(100.f,  100.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(10.f, 100.f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
        Vertex(10.f, 10.f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),

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
       // v[i] = Vertex(cos(i * 2 * pi / 100) * 50, sin(i * 2 * pi / 100) * 50, 0, 1, 1, 1, 1);
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
    context->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    xBasicCreateBuffer(device,
        D3D11_BIND_VERTEX_BUFFER,
        sizeof(Vertex) * 15,
        v,
        &squareVertBuffer
    );

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);
}
