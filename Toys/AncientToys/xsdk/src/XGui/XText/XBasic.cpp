#include "XBasic.h"
#include <Windows.h>
#include <d3dcompiler.h>

namespace
{
    int width = 100;
    int height = 500;

    const D3D11_INPUT_ELEMENT_DESC layout[2] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
}

void xBasicInitializeDirectX11(
    HWND hWnd, 
    IDXGISwapChain **SwapChain,
    ID3D11Device **device,
    ID3D11DeviceContext **context,
    ID3D11RenderTargetView **renderTargetView)
{
    *renderTargetView = nullptr;
    DXGI_MODE_DESC bufferDesc;

    ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

    bufferDesc.Width = width;
    bufferDesc.Height = height;
    bufferDesc.RefreshRate.Numerator = 60;
    bufferDesc.RefreshRate.Denominator = 1;
    bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    //Describe our SwapChain
    DXGI_SWAP_CHAIN_DESC swapChainDesc;

    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDesc.BufferDesc = bufferDesc;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

 
    //Create our SwapChain
    D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION, &swapChainDesc, SwapChain, device, NULL, context);

    D3D11_RASTERIZER_DESC rasterizerDesc;
    rasterizerDesc.AntialiasedLineEnable = false; // changed to true
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false; // changed to true
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    ID3D11RasterizerState *rstate;
    (*device)->CreateRasterizerState(&rasterizerDesc, &rstate);

    (*context)->RSSetState(rstate);
    
    xBasicChangeSize(*device, *context, *SwapChain, renderTargetView, 1, 1);
}

void xBasicCreateBuffer(
    ID3D11Device *device,
    UINT bindFlags,
    int byteWidth,
    void *pSysMem,
    ID3D11Buffer **buffer)
{
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = bindFlags;
    bd.ByteWidth = byteWidth;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    data.pSysMem = pSysMem;

    device->CreateBuffer(&bd, &data, buffer);
}

void xBasicCreateShader(
    ID3D11Device *device,
    ID3D11DeviceContext *context,
    LPCWSTR fileName,
    ID3D10Blob **VS_Buffer,
    ID3D10Blob **PS_Buffer,
    ID3D11VertexShader **VS,
    ID3D11PixelShader **PS)
{

    HRESULT hr;

    hr = D3DCompileFromFile(fileName, 0, 0, "VS", "vs_4_0", 0, 0, VS_Buffer, 0);
    hr = D3DCompileFromFile(fileName, 0, 0, "PS", "ps_4_0", 0, 0, PS_Buffer, 0);


    //Create the Shader Objects
    hr = device->CreateVertexShader((*VS_Buffer)->GetBufferPointer(), (*VS_Buffer)->GetBufferSize(), NULL, VS);
    hr = device->CreatePixelShader((*PS_Buffer)->GetBufferPointer(), (*PS_Buffer)->GetBufferSize(), NULL, PS);
    context->VSSetShader(*VS, 0, 0);
    context->PSSetShader(*PS, 0, 0);
}

void xBasicChangeSize(ID3D11Device * device, ID3D11DeviceContext * context, IDXGISwapChain * swapChain, ID3D11RenderTargetView ** renderTargetView, int width, int height)
{
    if (swapChain == nullptr)
    {
        return;
    }

    if (*renderTargetView)
    {
        (*renderTargetView)->Release();
    }

    swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
    ID3D11Texture2D *buffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&buffer);
    device->CreateRenderTargetView(buffer, NULL, renderTargetView);
    buffer->Release();
    context->OMSetRenderTargets(1, renderTargetView, NULL);
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = width - 100.0f;
    viewport.Height = height - 100.0f;
    viewport.MinDepth = 0;
    viewport.MaxDepth = 1;
    context->RSSetViewports(1, &viewport);
}
