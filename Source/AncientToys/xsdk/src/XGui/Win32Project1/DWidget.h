#ifndef DWIDGET_H
#define DWIDGET_H
#include <XRectangle.h>
#include "XEvent.h"
#include "DWindow.h"

class DWindow;

class DWidget
{
public:
    DWidget();
    ~DWidget();

public:
    virtual void onSize(XSizeEvent *event);
    virtual void onPaint(XPaintEvent *event);
    virtual void onMouseMove(XMouseEvent *event);
    virtual void onMouseDown(XMouseEvent *event);
    virtual void onCreate();

public:
    XRectangle boundary;
    DWindow *window;
};

#endif