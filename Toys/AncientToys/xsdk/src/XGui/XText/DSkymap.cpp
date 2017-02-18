#include "DSkymap.h"
#include <d3dcompiler.h>
#include <DDSTextureLoader.h>
#include <qmessagebox.h>
#include "XBasic.h"
#include <DirectXMath.h>

using namespace DirectX;

DSkymap::DSkymap(ID3D11Device * device)
    : device(device)
{
    countRows = 100;
    createSphere();
    initializeSkymap();
}

DSkymap::~DSkymap()
{
}

void DSkymap::draw(ID3D11DeviceContext *context)
{
    context->PSSetShaderResources(0, 1, &shaderResourceView);
    context->PSSetSamplers(0, 1, &cubeTextureSamplerState);
    context->VSSetShader(VS, NULL, 0);
    context->PSSetShader(PS, NULL, 0);
    context->OMSetDepthStencilState(depthStencilState, 0);
    context->RSSetState(rasterizerState);

    UINT stride = sizeof(Vertex2);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &sphereVertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

    context->DrawIndexed(countSphereIndices, 0, 0);
}

DirectX::XMFLOAT4X4 DSkymap::getWorld(const DCamera & camera)
{
    XMVECTOR camWorld = camera.getPositionXM();
    XMMATRIX tmpWorld = XMMatrixIdentity();
    tmpWorld *= XMMatrixTranslation(XMVectorGetX(camWorld), XMVectorGetY(camWorld), XMVectorGetZ(camWorld));

    XMFLOAT4X4 ans;
    XMStoreFloat4x4(&ans, tmpWorld);
    return ans;
}

DirectX::XMMATRIX DSkymap::getWorldXM(const DCamera & camera)
{
    XMVECTOR camWorld = camera.getPositionXM();
    XMMATRIX tmpWorld = XMMatrixIdentity();
    tmpWorld *= XMMatrixTranslation(XMVectorGetX(camWorld), XMVectorGetY(camWorld), XMVectorGetZ(camWorld));
    return tmpWorld;
}

void DSkymap::createSphere()
{
    int cntCP = countRows;
    int cntBallPoints = (2 * cntCP + 1) * cntCP;
    float seed = 1.0f / (float)(cntCP);
    Vertex2 *vecBall = new Vertex2[cntBallPoints];
    for (int i = 0; i < cntCP * 2 + 1; i++)
    {
        for (int j = 0; j < cntCP; j++)
        {
            float z = 1.0f - i * seed;
            float r = sqrt(1.0f - z * z);
            float x = r * cos(2 * XM_PI * (j / (float)cntCP));
            float y = r * sin(2 * XM_PI * (j / (float)cntCP));
            static int times = 0;
            times++;
            times = rand() % 3;

            vecBall[i * cntCP + j] = Vertex2(x, y, z, rand() % 2, rand() % 2);
        }
    }
    // xBasicCreateBuffer(D3D11_BIND_VERTEX_BUFFER, vecBall, sizeof(Vertex) * cntBallPoints, &vertexBuffer);
    xBasicCreateBuffer(device, D3D11_BIND_VERTEX_BUFFER, sizeof(Vertex2) * cntBallPoints, vecBall, &sphereVertexBuffer);
    delete[] vecBall;

    int cntBallIndices = 0;
    DWORD *indexBall = new DWORD[cntCP * 2 * cntCP * 6];
    for (int i = 0; i < cntCP * 2; i++)
    {
        for (int j = 0; j < cntCP; j++)
        {
            indexBall[cntBallIndices++] = i * cntCP + j;
            indexBall[cntBallIndices++] = (i + 1) * cntCP + ((j + 1) % cntCP);
            indexBall[cntBallIndices++] = (i + 1) * cntCP + j;

            indexBall[cntBallIndices++] = i * cntCP + (j + 1) % cntCP;
            indexBall[cntBallIndices++] = (i + 1) * cntCP + ((j + 1) % cntCP);
            indexBall[cntBallIndices++] = i * cntCP + j;

        }
    }

    xBasicCreateBuffer(device, D3D11_BIND_INDEX_BUFFER, sizeof(DWORD) * cntBallIndices, indexBall, &sphereIndexBuffer);
    delete[] indexBall;
    countSphereIndices = cntBallIndices;
}

void DSkymap::initializeSkymap()
{
    D3DCompileFromFile(L"Effects.fx", NULL, NULL, "skymap_VS", "vs_5_0", 0, 0, &VSBuffer, NULL);
    D3DCompileFromFile(L"Effects.fx", NULL, NULL, "skymap_PS", "ps_5_0", 0, 0, &PSBuffer, NULL);

    device->CreateVertexShader(VSBuffer->GetBufferPointer(), VSBuffer->GetBufferSize(), NULL, &VS);
    device->CreatePixelShader(PSBuffer->GetBufferPointer(), PSBuffer->GetBufferSize(), NULL, &PS);

    ID3D11Texture2D *texture;
    HRESULT hr = CreateDDSTextureFromFile(device, L"Textures/CubeMap/skyMap02.dds", (ID3D11Resource **)&texture, NULL);
    if (FAILED(hr))
    {
        QMessageBox::information(nullptr, "FAILE", "FAILURE");
    }

    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
    texture->GetDesc(&textureDesc);

    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    ZeroMemory(&shaderResourceViewDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
    shaderResourceViewDesc.Format = textureDesc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D10_1_SRV_DIMENSION_TEXTURECUBE;
    shaderResourceViewDesc.TextureCube.MipLevels = textureDesc.MipLevels;
    shaderResourceViewDesc.TextureCube.MostDetailedMip = 0;
    device->CreateShaderResourceView(texture, &shaderResourceViewDesc, &shaderResourceView);

    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = true;
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);

    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
//    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
    device->CreateSamplerState(&samplerDesc, &cubeTextureSamplerState);
}
