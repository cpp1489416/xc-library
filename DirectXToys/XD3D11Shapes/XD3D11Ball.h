#pragma once
#include "XVirtualD3D11Shape.h"

class XD3D11Ball :
	public XVirtualD3D11Shape
{
public:
	XD3D11Ball(XVirtualD3D11Drawer *parent);
	virtual ~XD3D11Ball();
	void create(int countCirclePoints);
	void draw();
	void setSolid(bool solid);

protected:
    virtual void onPaint();

	bool solid;
	int cntCirclePoints;
	int cntBallPoints;
	int cntBallIndices;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;
};

