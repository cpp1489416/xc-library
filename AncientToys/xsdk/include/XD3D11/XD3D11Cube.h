#pragma once
#include "XVirtualD3D11Shape.h"
class XD3D11Cube :
	public XVirtualD3D11Shape
{
public:
	XD3D11Cube(XVirtualD3D11Drawer *parent);
	virtual ~XD3D11Cube();
	void create();
	void draw();
	void setSolid(bool solid);

protected:
	bool solid;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
};

