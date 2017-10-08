#include "DPainter.h"
#include <ctime>
#include <cstdlib>
#include "XBasic.h"
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include <d3dcompiler.h>
#include <qmessagebox.h>

using namespace std;

namespace
{
    static const float PI = 3;
}

DPainter::DPainter()
{
    D3D11_SRV_DIMENSION_TEXTURECUBE;
//    CreateDDSTextureFromFile(device, L"abc.dds", &cubeTexture, nullptr, )
}


DPainter::~DPainter()
{
}

void DPainter::createSphere(int countRows, int countColumns)
{

    srand(time(nullptr));

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
            float x = r * cos(2 * PI * (j / (float)cntCP));
            float y = r * sin(2 * PI * (j / (float)cntCP));
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
    cntSphereVretices = cntBallIndices;
}

void DPainter::drawSphere()
{
    UINT stride = sizeof(Vertex2);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &sphereVertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    context->DrawIndexed(10000000, 0, 0);
}

void DPainter::createCube()
{
    HRESULT hr = CreateWICTextureFromFile(device, L"Textures//Wood_MetalStripes.bmp", nullptr, &cubeTexture);
    hr = CreateWICTextureFromFile(device, L"Textures//Ball_Paper.bmp", nullptr, &cubeTextures[0]);
    hr = CreateWICTextureFromFile(device, L"Textures//Ball_Stone.bmp", nullptr, &cubeTextures[1]);
    hr = CreateWICTextureFromFile(device, L"Textures//Wood_MetalStripes.bmp", nullptr, &cubeTextures[2]);

    if (FAILED(hr))
    {
        return;
    }
    Vertex2 v[] =
    {
        // Front Face
        Vertex2(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex2(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Vertex2(1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex2(1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Back Face
        Vertex2(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f),
        Vertex2(1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
        Vertex2(1.0f,  1.0f, 1.0f, 0.0f, 0.0f),
        Vertex2(-1.0f,  1.0f, 1.0f, 1.0f, 0.0f),

        // Top Face
        Vertex2(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f),
        Vertex2(-1.0f, 1.0f,  1.0f, 0.0f, 0.0f),
        Vertex2(1.0f, 1.0f,  1.0f, 1.0f, 0.0f),
        Vertex2(1.0f, 1.0f, -1.0f, 1.0f, 1.0f),

        // Bottom Face
        Vertex2(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),
        Vertex2(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex2(1.0f, -1.0f,  1.0f, 0.0f, 0.0f),
        Vertex2(-1.0f, -1.0f,  1.0f, 1.0f, 0.0f),

        // Left Face
        Vertex2(-1.0f, -1.0f,  1.0f, 0.0f, 1.0f),
        Vertex2(-1.0f,  1.0f,  1.0f, 0.0f, 0.0f),
        Vertex2(-1.0f,  1.0f, -1.0f, 1.0f, 0.0f),
        Vertex2(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f),

        // Right Face
        Vertex2(1.0f, -1.0f, -1.0f, 0.0f, 1.0f),
        Vertex2(1.0f,  1.0f, -1.0f, 0.0f, 0.0f),
        Vertex2(1.0f,  1.0f,  1.0f, 1.0f, 0.0f),
        Vertex2(1.0f, -1.0f,  1.0f, 1.0f, 1.0f),
    };

    DWORD indices[] = {
        // Front Face
        0,  1,  2,
        0,  2,  3,

        // Back Face
        4,  5,  6,
        4,  6,  7,

        // Top Face
        8,  9, 10,
        8, 10, 11,

        // Bottom Face
        12, 13, 14,
        12, 14, 15,

        // Left Face
        16, 17, 18,
        16, 18, 19,

        // Right Face
        20, 21, 22,
        20, 22, 23
    };

    ::xBasicCreateBuffer(device, D3D11_BIND_INDEX_BUFFER, sizeof(UINT) * 12 * 3, indices, &cubeIndexBuffer);
   
    ::xBasicCreateBuffer(device, D3D11_BIND_VERTEX_BUFFER, sizeof(Vertex2) * 24, v, &cubeVertexBuffer);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = device->CreateSamplerState(&sampDesc, &cubeTextureSamplerState);
    if (FAILED(hr))
    {
        return;;
    }
}

void DPainter::drawCube(int textureIndex)
{
    UINT stride = sizeof(Vertex2);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &cubeVertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(cubeIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
    context->PSSetSamplers(0, 1, &cubeTextureSamplerState);
    context->PSSetShaderResources(0, 1, &cubeTextures[textureIndex % 3]);

    context->DrawIndexed(36, 0, 0);
}