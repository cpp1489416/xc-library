#pragma once
#include <d3d11.h>
#include <DirectXMath.h>

void xBasicInitializeDirectX11(
    HWND hWnd,
    IDXGISwapChain **SwapChain,
    ID3D11Device **device,
    ID3D11DeviceContext **d3d11DevCon,
    ID3D11RenderTargetView **renderTargetView
);

void xBasicCreateBuffer(
    ID3D11Device *device,
    UINT bindFlags,
    int byteWidth,
    void *pSysMem,
    ID3D11Buffer **buffer
);

void xBasicCreateShader(
    ID3D11Device *device,
    ID3D11DeviceContext *context,
    LPCWSTR fileName,
    ID3D10Blob **VS_Buffer,
    ID3D10Blob **PS_Buffer,
    ID3D11VertexShader **VS,
    ID3D11PixelShader **PS
);

void xBasicChangeSize(
    ID3D11Device *device,
    ID3D11DeviceContext *context,
    IDXGISwapChain *swapChain,
    ID3D11RenderTargetView **renderTargetView,
    int width,
    int height
);