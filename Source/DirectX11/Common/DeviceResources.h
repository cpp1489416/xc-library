#pragma once

#include "DirectX11Includes.h"

namespace XC
{
    namespace DirectX11
    {
        namespace Common
        {
            class DeivceResources
            {
            public:
                DeivceResources();

            public:
                void SetHWND(const HWND & hWND);
                void SetSize(int width, int height);

                // getters
                ID3D11Device * GetD3DDevice() { return mD3DDevice.Get(); }
                ID3D11DeviceContext * GetD3DDeviceContext() { return mD3DContext.Get(); }
                ID3D11RenderTargetView * GetBackBufferRenderTarGetView() { return mD3DRenderTarGetView.Get(); }
                ID3D11DepthStencilView * GetDepthStencilView() { return mD3DDepthStencilView.Get(); }
                D3D11_VIEWPORT * GetScreenViewport() { return &mScreenViewport; }
                HWND GetHWND() { return mHWND; }

            private:
                // D3D11 objects, must
                Microsoft::WRL::ComPtr<ID3D11Device> mD3DDevice;
                Microsoft::WRL::ComPtr<ID3D11DeviceContext> mD3DContext;
                Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
                
                // D3D11 render objects, must
                Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mD3DRenderTarGetView;
                Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mD3DDepthStencilView;
                D3D11_VIEWPORT mScreenViewport;

                // windows api
                HWND mHWND;
            };
        }
    }
}