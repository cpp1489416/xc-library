#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3d11.h>


using namespace DirectX;

struct Vertex;
struct CPerObject;
class DWidget;
class DPainter;

struct Vertex
{
    Vertex()
    {

    }

    Vertex(float x, float y, float z, float r, float g, float b, float a)
        : pos(x, y, z), color(r, g, b, a)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT4 color;
};

struct Vertex2
{
    Vertex2()
    {

    }

    Vertex2(float x, float y, float z, float u, float v)
        : pos(x, y, z), texCood(u, v)
    {

    }

    XMFLOAT3 pos;
    XMFLOAT2 texCood;
};

struct CPerObject
{
    XMFLOAT4X4 world;
    XMFLOAT4X4 view;
    XMFLOAT4X4 projection;
};

class DPainter
{
public:
    DPainter();
    ~DPainter();
    void createSphere(int countRows, int countColumns);
    void createCube();
    void drawSphere();
    void drawCube(int textureIndex = 0);
public:
    ID3D11Device *device;
    ID3D11DeviceContext *context;


    ID3D11Buffer *sphereVertexBuffer;
    ID3D11Buffer *sphereIndexBuffer;

    ID3D11Buffer *cubeVertexBuffer;
    ID3D11Buffer *cubeIndexBuffer;
    ID3D11ShaderResourceView *cubeTexture;
    ID3D11ShaderResourceView *cubeTextures[3];
    ID3D11SamplerState *cubeTextureSamplerState;


    
    int cntSphereVretices;
};

