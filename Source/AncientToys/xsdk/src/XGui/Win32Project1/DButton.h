#pragma once
#include "DWidget.h"

class DButton :
    public DWidget
{
public:
    DButton();
    ~DButton();

public:
    virtual void onPaint(XPaintEvent *event);
    virtual void onSize(XSizeEvent *event);
    virtual void onMouseDown(XMouseEvent *event);
    virtual void onCreate();

private:
    bool initialized;
    void initializeD3D();
    ID3D11Buffer *vertexBuffer;
};

