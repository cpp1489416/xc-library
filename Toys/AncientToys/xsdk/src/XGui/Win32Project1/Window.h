#ifndef WINDOW_H
#define WINDOW_H

#include "Window.h"
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include  "Ball.h"

using namespace DirectX;

struct Vertex
{
    Vertex()
    {

    }

    Vertex(float x, float y, float z, float r, float g, float b, float a)
        : pos(x, y, z), color(r, g, b, a)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct cbPerObject
{
    XMFLOAT4X4 WVP;
};


class Window
{
public:
    Window() {}
    ~Window() {}

    void show();

public:
    inline void update() { D3DRender(); }
    static LRESULT CALLBACK xwndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void initializeD3D();
    void D3DSizeChanged();
    void D3DRender();

    HWND hWnd;
    HINSTANCE hInstance;
    int nCmdShow;
    LPCWSTR className = L"gege";
    int width;
    int height;

    ID3D11Device *device;
    ID3D11DeviceContext *context;
    IDXGISwapChain *swapChain;
    ID3D11RenderTargetView *renderTargetView;
    ID3D11VertexShader *VS;
    ID3D11PixelShader *PS;
    ID3DBlob *VS_Buffer;
    ID3DBlob *PS_Buffer;
    ID3D11Buffer *triangleVertBuffer;
    ID3D11InputLayout *vertLayout;

    const D3D11_INPUT_ELEMENT_DESC layout[2] =
    {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    int numElements = 200;

    XMFLOAT4X4 WVP;
    XMFLOAT4X4 world;
    XMFLOAT4X4 camView;
    XMFLOAT4X4 camProjection;

    XMFLOAT4 camPosition;
    XMFLOAT4 camTarget;
    XMFLOAT4 camUp;

    cbPerObject cbPerObj;
    ID3D11Buffer *cbPerObjectBuffer;
    ID3D11Buffer *squareIndexBuffer;
    ID3D11Buffer *squareVertBuffer;

    ID3D11DepthStencilView *depthStencilView;
    ID3D11Texture2D *depthStencilBuffer;
};
#endif