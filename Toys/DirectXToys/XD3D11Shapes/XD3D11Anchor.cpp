#include "stdafx.h"
#include "XD3D11Anchor.h"

XD3D11Anchor::XD3D11Anchor(XVirtualD3D11Drawer * parent)
	: XVirtualD3D11Shape(parent)
{
}

XD3D11Anchor::~XD3D11Anchor()
{
	vertexBuffer->Release();
}

void XD3D11Anchor::create()
{
	XVirtualD3D11Drawer::Vertex anVert[] =
	{
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
		{ XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) },
	};
	parent->XCreateSimpleBuffer(D3D11_BIND_VERTEX_BUFFER, anVert, sizeof(anVert), &vertexBuffer);
}

void XD3D11Anchor::draw()
{
	UINT stride = sizeof(XVirtualD3D11Drawer::Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	context->Draw(6, 0);
}

