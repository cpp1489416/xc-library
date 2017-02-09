#include "DeviceResources.h"
#include <algorithm>

namespace
{
	HRESULT gHR;
}

namespace XC
{
	namespace DirectX11
	{
		namespace Common
		{
			DeviceResources::DeviceResources() :
				mWidth(800),
				mHeight(600),
				mCreated(false)
			{
			}

			void DeviceResources::SetSize(int width, int height)
			{
				mWidth = width;
				mHeight = height;

				if (mCreated)
				{
					mCreated = true;
					RecreateSizeDependentResources();
				}
			}

			void DeviceResources::Initialize()
			{
				if (!mCreated)
				{
					CreateDevice();
				}
			}

			void DeviceResources::Present()
			{
				mSwapChain->Present(0, 0);
			}

			void DeviceResources::CreateDevice()
			{
				// specific swap chain first
				// swap chain buffer
				DXGI_MODE_DESC bufferDesc = { 0 };
				bufferDesc.Width = mWidth;
				bufferDesc.Height = mHeight;
				bufferDesc.RefreshRate.Numerator = 60;
				bufferDesc.RefreshRate.Denominator = 1;
				bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
				bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

				// swap chain desc
				DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
				swapChainDesc.BufferDesc = bufferDesc;
				swapChainDesc.SampleDesc.Count = 1;
				swapChainDesc.SampleDesc.Quality = 0;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.BufferCount = 1;
				swapChainDesc.OutputWindow = mHWND;
				swapChainDesc.Windowed = TRUE;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

				// create device and swap chain
				gHR = D3D11CreateDeviceAndSwapChain(
					nullptr, // no adapter
					D3D_DRIVER_TYPE_HARDWARE, // must hardware
					0, // not software
					0, // no flag
					nullptr, // feature level, 0 to the higest level
					0, // count of feature levels
					D3D11_SDK_VERSION, // sdk version
					&swapChainDesc, // swap chain desc
					&mSwapChain,
					&mD3DDevice, // device
					nullptr, // pFeatureLevel, for backwards compatibility
					&mD3DContext // device context
				);

				ThrowIfError();

				// create back buffer
				ID3D11Texture2D * backBuffer;
				gHR = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void * *)&backBuffer);
				ThrowIfError();

				// create render target
				gHR = mD3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mD3DRenderTargetView);
				ThrowIfError();
				backBuffer->Release();

				// set render target
				mD3DContext->OMSetRenderTargets(1, mD3DRenderTargetView.GetAddressOf(), nullptr);

				mViewport = D3D11_VIEWPORT{ 0 };
				mViewport.TopLeftX = 0;
				mViewport.TopLeftY = 0;
				mViewport.Width = mWidth;
				mViewport.Height = mHeight;
				mD3DContext->RSSetViewports(1, &mViewport);
			}

			void DeviceResources::RecreateSizeDependentResources()
			{
				// context null view
				ID3D11RenderTargetView	*nullViews[] = { nullptr };
				mD3DContext->OMSetRenderTargets(0, nullptr, nullptr);

				// renderTargetView and DepthStencilView to null
				mD3DRenderTargetView = nullptr;
				mD3DDepthStencilView = nullptr;

				// window size must bigger than q
				mWidth = mWidth > 1 ? mWidth : 1;
				mHeight = mHeight > 1 ? mHeight : 1;

				// swap chain 
				gHR = mSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
				ThrowIfError();

				// recreate backbuffer
				ID3D11Texture2D * buffer;
				gHR = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void * *)&buffer);
				ThrowIfError();

				// recreate render target
				gHR = mD3DDevice->CreateRenderTargetView(buffer, nullptr, mD3DRenderTargetView.GetAddressOf());
				ThrowIfError();
				buffer->Release();

				// set render target
				ID3D11RenderTargetView * renderTargetView = mD3DRenderTargetView.Get();
				mD3DContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
				mViewport.Width = mWidth;
				mViewport.Height = mHeight;
				mD3DContext->RSSetViewports(1, &mViewport);
			}

			void DeviceResources::ThrowIfError(const char * information)
			{
				if (FAILED(gHR))
				{
					throw;
				}
			}
		}
	}
}
