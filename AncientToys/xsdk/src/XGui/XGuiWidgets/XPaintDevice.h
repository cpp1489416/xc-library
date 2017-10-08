#pragma once
#include <XAutoPointer.h>
#include "XEvent.h"

class XPaintDevicePrivate;

class XPaintDevice
{
public:
    XPaintDevice();
    ~XPaintDevice();
    XPaintDevicePrivate getPrivate();

protected:
    virtual void onPaint(XPaintEvent *event);

private:
    XAutoPointer<XPaintDevicePrivate> m;
};

