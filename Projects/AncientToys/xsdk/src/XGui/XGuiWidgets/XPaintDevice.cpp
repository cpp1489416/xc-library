#include "stdafx.h"
#include "XPaintDevice.h"

class XPaintDevicePrivate
{
public:

};

XPaintDevice::XPaintDevice()
{
}

XPaintDevice::~XPaintDevice()
{
}

XPaintDevicePrivate XPaintDevice::getPrivate()
{
    return XPaintDevicePrivate();
}

void XPaintDevice::onPaint(XPaintEvent *event)
{

}
