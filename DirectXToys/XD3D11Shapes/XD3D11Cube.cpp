#include "stdafx.h"
#include "XD3D11Cube.h"

XD3D11Cube::XD3D11Cube(XVirtualD3D11Drawer * parent)
	: XVirtualD3D11Shape(parent)
{
	solid = false;
}

XD3D11Cube::~XD3D11Cube()
{
	vertexBuffer->Release();
	indexBuffer->Release();
}

void XD3D11Cube::create()
{
	XVirtualD3D11Drawer::Vertex vertices[] =
	{
		{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	};
	parent->XCreateSimpleBuffer(D3D11_BIND_VERTEX_BUFFER, vertices, sizeof(vertices), &vertexBuffer);

	// Create index buffer
	DWORD indices[] =
	{
		//
		3,1,0,
		2,1,3,
		//
		0,5,4,
		1,5,0,
		//
		3,4,7,
		0,4,3,
		//
		1,6,5,
		2,6,1,
		//
		2,7,6,
		3,7,2,
		//
		6,4,5,
		7,4,6,
	};
	parent->XCreateSimpleBuffer(D3D11_BIND_INDEX_BUFFER, indices, sizeof(indices), &indexBuffer);
}

void XD3D11Cube::draw()
{
	UINT stride = sizeof(XVirtualD3D11Drawer::Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	if (solid)
	{
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
	else
	{
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	}
	context->DrawIndexed(36, 0, 0);
}

void XD3D11Cube::setSolid(bool solid)
{
	this->solid = solid;
}
