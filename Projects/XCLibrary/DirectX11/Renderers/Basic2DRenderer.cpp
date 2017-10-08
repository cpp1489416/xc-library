#include "Basic2DRenderer.h"
#include "../Shaders/ShaderStructures.h"

using namespace XC::DirectX11::Renderers;
using namespace XC::DirectX11::Common;
using namespace XC::DirectX11::Shaders::ShaderStructures;

namespace
{
}

namespace XC
{
    namespace DirectX11
    {
        namespace Renderers
        {

            Basic2DRenderer::Basic2DRenderer(Common::DeviceResources * deviceResources) :
                Renderer(deviceResources)
            {
                mDevice = deviceResources->GetD3DDevice();
                mContext = deviceResources->GetD3DDeviceContext();

                // compile shader

                Microsoft::WRL::ComPtr<ID3DBlob> mVertexShaderBuffer;
                Microsoft::WRL::ComPtr<ID3DBlob> mPixelShaderBuffer;

                D3DCompileFromFile(L"Shaders/Basic2DVertexShader.hlsl", nullptr, nullptr, "main", "vs_4_0", 0, 0, mVertexShaderBuffer.GetAddressOf(), nullptr);
                D3DCompileFromFile(L"Shaders/Basic2DPixelShader.hlsl", nullptr, nullptr, "main", "ps_4_0", 0, 0, mPixelShaderBuffer.GetAddressOf(), nullptr);

                mDevice->CreateVertexShader(mVertexShaderBuffer->GetBufferPointer(), mVertexShaderBuffer->GetBufferSize(), nullptr, mVertexShader.GetAddressOf());
                mDevice->CreatePixelShader(mPixelShaderBuffer->GetBufferPointer(), mPixelShaderBuffer->GetBufferSize(), nullptr, mPixelShader.GetAddressOf());

                mContext->VSSetShader(mVertexShader.Get(), nullptr, 0);
                mContext->PSSetShader(mPixelShader.Get(), nullptr, 0);

                VertexPosition positions[] =
                {
                        {{1, 1, 1}},
                        {{2, 2, 2}},
                };
            }

            void Basic2DRenderer::OnUpdate()
            {
            }

            void Basic2DRenderer::OnRender()
            {
            }
        }
    }
}