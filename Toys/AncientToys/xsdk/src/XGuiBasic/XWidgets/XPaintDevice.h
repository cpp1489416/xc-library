#pragma once
#include <XAutoPointer.h>

class XPaintDevicePrivate;

class XPaintDevice
{
public:
    XPaintDevice();
    ~XPaintDevice();
    XPaintDevicePrivate getPrivate();

protected:
    virtual void onPaint();

private:
    XAutoPointer<XPaintDevicePrivate> m;
};

