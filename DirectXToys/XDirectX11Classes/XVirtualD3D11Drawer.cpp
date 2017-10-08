#include "XVirtualD3D11Drawer.h"



XVirtualD3D11Drawer::XVirtualD3D11Drawer()
{
}

XVirtualD3D11Drawer::~XVirtualD3D11Drawer()
{
	device->Release();
	context->Release();
	swapChain->Release();
	renderTargetView->Release();
	//depthStencilView->Release();
	//depthStencilBuffer->Release();
}

bool XVirtualD3D11Drawer::initializeD3D11App()
{
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Height = height;
	bufferDesc.Width = width;
	bufferDesc.RefreshRate.Denominator = 1;	
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 4;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        NULL,
        &context
    );

	ID3D11Texture2D *backBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBuffer);
	device->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	backBuffer->Release();
	// context->OMSetRenderTargets(1, &renderTargetView, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 0;
	depthStencilDesc.SampleDesc.Count = 4;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.Width = width;
	device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	context->OMSetRenderTargets(1, &renderTargetView, NULL);

	return true;
}

void XVirtualD3D11Drawer::initializeScene()
{
	// do nothing
}

void XVirtualD3D11Drawer::update()
{
	// do nothing
}

void XVirtualD3D11Drawer::draw()
{
	static float x = 0.0f;
	x += 0.001f;
	if (x >= 1.0)
		x = 0.0f;
	float backColors[] = { x, 0.0f, 1.0f, 1.0f };
	context->ClearRenderTargetView(renderTargetView, backColors);

	swapChain->Present(0, 0);
}

void XVirtualD3D11Drawer::XCreateSimpleBuffer(UINT bindFlags, const void * pSysMem, UINT byteWidth, ID3D11Buffer ** buffer)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = byteWidth;
	bd.BindFlags = bindFlags;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(data));
	data.pSysMem = pSysMem;
	device->CreateBuffer(&bd, &data, buffer);
}

void XVirtualD3D11Drawer::XCreateSimpleBufferNull(UINT bindFlags, UINT byteWidth, ID3D11Buffer ** buffer)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = byteWidth;
	bd.BindFlags = bindFlags;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;

	device->CreateBuffer(&bd, NULL, buffer);
}