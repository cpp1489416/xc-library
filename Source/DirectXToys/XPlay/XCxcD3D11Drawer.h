#pragma once
#include <XVirtualD3D11Drawer.h>
#include <XD3D11Ball.h>
#include <DirectXMath.h>
#include <XD3D11Cube.h>

#pragma comment (lib, "XD3D11Shapes.lib")
using namespace DirectX;

struct ConstantBuffer
{
    XMFLOAT4X4 World;
    XMFLOAT4X4 View;
    XMFLOAT4X4 Projection;
};

class XCxcD3D11Drawer :
	public XVirtualD3D11Drawer
{
public:
	XCxcD3D11Drawer();
	virtual ~XCxcD3D11Drawer();


	void initializeScene();
	virtual void update();
	virtual void draw();
	void rotateY(float ang);
	void rotateX(float ang);
	void rotateZ(float ang);

protected:
 //   DirectX::XMFLOAT4X4 world;
  //  DirectX::XMFLOAT4X4 view;
  //  DirectX::XMFLOAT4X4 projection;
	ID3D11Buffer *constantBuffer;

	ID3D11InputLayout *vertexLayout;

	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;
	ID3D10Blob *vertexShaderBuffer;
	ID3D10Blob *pixelShaderBuffer;

	XD3D11Ball *ball;
    XD3D11Cube *cube;
};

