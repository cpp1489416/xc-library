#pragma once
#include <XAutoPointer.h>
#include <XRectangle.h>
#include <XString.h>
#include <string>
#include "XEvent.h"
#include "XPaintDevice.h"
#include "XWindowsDefines.h"
#include <Windows.h>
#include <vector>

using namespace std;
//class XWidget;

class XWidget
{
public:
    XWidget();
    virtual ~XWidget();
    void show(XWidget *parent = nullptr);
    void setBoundary(const XRectangle &rectangle);
    XRectangle getBoundary() const;
    void addWidget(XWidget *widget);
    XWidget *getParent() const;
    HWND win32GetHwnd() const;

protected:
    virtual void onKeyPressed();
    virtual void onPaint(XPaintEvent *event);
    virtual void onSize(XSizeEvent *event);
    virtual void onMouseMove(XMouseEvent *event);
    virtual void win32OnCommand(HWND hWnd, long wParam, long lParam);
    virtual void win32OnCreate(HWND hWnd, long wParam, long lParam);

private:
    void subInitialize();
    void win32CreateClass();
    static LRESULT CALLBACK staticWindowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT windowProcess(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    XRectangle boundary;
    static LPCTSTR wndClassName;
    static int countWindows;
    LPCTSTR title;
    HWND hWnd;
    XWidget *parent;
    std::vector<XWidget *> childs;
    XSizeEvent sizeEvent;
    XWidget *self;
    XPaintEvent paintEvent;
};

