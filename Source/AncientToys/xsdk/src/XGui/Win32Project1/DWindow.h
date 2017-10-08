#ifndef DWINDOW_H
#define DWINDOW_H
#include <Windows.h>
#include "DWidget.h"
#include "XEvent.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "Window.h"

using namespace DirectX;

class DWidget; 

struct CPerObject
{
    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
};

class DWindow
{
public:
    DWindow();
    ~DWindow();
    void show();
    void addWidget(DWidget *widget);
    void updateConstantBuffer();
    void rotateX();
    void rotateY();
    void rotateZ();

protected:

public:
    static LRESULT CALLBACK staticWindowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT windowProcess(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void registerClass();
    void initializeDirectX();
    void onSize(XSizeEvent *event);
    void onPaint(XPaintEvent *event);
    void onMouseDown(XMouseEvent *event);
    void onMouseMove(XMouseEvent *event);
    void onDestory();
    void updateWVP();

    HWND hwnd;
    DWidget *widget;
    static DWindow *self;
    XSizeEvent sizeEvent;
    XPaintEvent paintEvent;
    XMouseEvent mouseEvent;

    ID3D11Device *device;
    ID3D11DeviceContext *context;
    IDXGISwapChain *swapChain;
    ID3D11RenderTargetView *renderTargetView;
    ID3D11VertexShader *VS;
    ID3D11PixelShader *PS;
    ID3D10Blob *VS_Buffer;
    ID3D10Blob *PS_Buffer;
    ID3D11Buffer *constantBuffer;
    ID3D11InputLayout *vertexLayout;
    ID3D11Buffer *worldBuffer;
    ID3D11Buffer *viewBuffer;
    ID3D11Buffer *projectionBuffer;

    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
    XMFLOAT4 eye;
    XMFLOAT4 target;
    XMFLOAT4 up;
    CPerObject WVP;

    const D3D11_INPUT_ELEMENT_DESC layout[2] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    int numElements = 200;
};

#endif