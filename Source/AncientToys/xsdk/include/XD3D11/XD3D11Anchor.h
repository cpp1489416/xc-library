#pragma once
#include "XVirtualD3D11Shape.h"
class XD3D11Anchor :
	public XVirtualD3D11Shape
{
public:
	XD3D11Anchor(XVirtualD3D11Drawer *parent);
	virtual ~XD3D11Anchor();
	void create();
	void draw();

protected:
	ID3D11Buffer *vertexBuffer;
};

