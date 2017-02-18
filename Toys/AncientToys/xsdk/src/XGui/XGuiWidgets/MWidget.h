#pragma once
#include "XWidget.h"
#include "XButton.h"

class MWidget : public XWidget
{
public:
    MWidget();
    ~MWidget();

    void clickedSlot();
protected:
    virtual void win32OnCreate(HWND hWnd, long wParam, long lParam)
    {

    }

    virtual void onCreate()
    {

    }

    virtual void onSize(XSizeEvent *event);

private:
    XButton *buttonArr[19][19];
};

