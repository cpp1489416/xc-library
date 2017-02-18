#pragma once
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <xnamath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

class XVirtualD3D11Drawer
{
public:
	struct Vertex
	{
		void set(float x, float y, float z, float r, float g, float b, float a)
		{
			position = XMFLOAT3(x, y, z);
			color = XMFLOAT4(r, g, b, a);
		}

		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	XVirtualD3D11Drawer();
	virtual ~XVirtualD3D11Drawer();
	void setHWND(HWND hWnd);
	void setWidth(int width);
	void setHeight(int height);
	ID3D11Device *getDevice() const;
	ID3D11DeviceContext *getContext() const;
	bool initializeD3D11App();
	virtual void initializeScene();
	virtual void update();
	virtual void draw();
	void XCreateSimpleBuffer(UINT bindFlags, const void * pSysMem, UINT byteWidth, ID3D11Buffer ** buffer);
	void XCreateSimpleBufferNull(UINT bindFlags, UINT byteWidth, ID3D11Buffer ** buffer);

protected:
//	void XCreateSimpleLayout(LPCWSTR srcFile, LPCSTR functionName, ID3D10Blob * *shaderBuffer, );

	ID3D11Device *device;
	ID3D11DeviceContext *context;
	IDXGISwapChain *swapChain;
	ID3D11RenderTargetView *renderTargetView;
	ID3D11DepthStencilView *depthStencilView;
	ID3D11Texture2D	*depthStencilBuffer;
	HWND hWnd;
	int height;
	int width;
};

