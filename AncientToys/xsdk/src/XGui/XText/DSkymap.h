#pragma once
#include <d3d11.h>
#include "DPainter.h"
#include "DCamera.h"
#include <DirectXMath.h>
class DSkymap
{
public:
    DSkymap(ID3D11Device *device);
    ~DSkymap();
    void draw(ID3D11DeviceContext *context);
    DirectX::XMFLOAT4X4 getWorld(const DCamera& camera); 
    DirectX::XMMATRIX getWorldXM(const DCamera& camera);

private: public:
    void createSphere();
    void initializeSkymap();

    ID3D11Device *device;

    ID3D11Buffer *sphereVertexBuffer;
    ID3D11Buffer *sphereIndexBuffer;
    ID3D11ShaderResourceView *shaderResourceView;
    ID3D11RasterizerState *rasterizerState;
    ID3D11DepthStencilState *depthStencilState;
    ID3D11SamplerState *cubeTextureSamplerState;
   
    ID3DBlob *VSBuffer;
    ID3DBlob *PSBuffer;
    ID3D11VertexShader *VS;
    ID3D11PixelShader *PS;

    UINT countRows;
    UINT countSphereIndices;
};

