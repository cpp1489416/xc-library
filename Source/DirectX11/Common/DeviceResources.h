#pragma once

#include "DirectX11Includes.h"

namespace XC
{
    namespace DirectX11
    {
        namespace Common
        {
            class DeviceResources
            {
            public:
                DeviceResources();

            public:
				void SetHWND(const HWND & hWND) { mHWND = hWND; }
                void SetSize(int width, int height);
				void Initialize();
				void Present();

                // getters
                ID3D11Device * GetD3DDevice() { return mD3DDevice.Get(); }
                ID3D11DeviceContext * GetD3DDeviceContext() { return mD3DContext.Get(); }
                ID3D11RenderTargetView * GetBackBufferRenderTarGetView() { return mD3DRenderTargetView.Get(); }
                ID3D11DepthStencilView * GetDepthStencilView() { return mD3DDepthStencilView.Get(); }
                D3D11_VIEWPORT * GetViewport() { return &mViewport; }
                HWND GetHWND() { return mHWND; }

			private:
				void CreateDevice();
				void RecreateSizeDependentResources();
				void ThrowIfError(const char * informatrion = "");
				
            private:
                // D3D11 objects, must
                Microsoft::WRL::ComPtr<ID3D11Device> mD3DDevice;
                Microsoft::WRL::ComPtr<ID3D11DeviceContext> mD3DContext;
                Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
                
                // D3D11 render objects, must
                Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mD3DRenderTargetView;
                Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mD3DDepthStencilView;
                D3D11_VIEWPORT mViewport;

                // windows api
                HWND mHWND;

				// window size
				int mWidth = 800;
				int mHeight = 600;

				bool mCreated = false;
            };
        }
    }
}