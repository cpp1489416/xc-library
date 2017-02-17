#include "stdafx.h"
#include "XVirtualD3D11Shape.h"

XVirtualD3D11Shape::XVirtualD3D11Shape(XVirtualD3D11Drawer * parent)
{
	this->device = parent->getDevice();
	this->context = parent->getContext();
	this->parent = parent;
}

XVirtualD3D11Shape::~XVirtualD3D11Shape()
{
}

void XVirtualD3D11Shape::onPaint()
{
}
