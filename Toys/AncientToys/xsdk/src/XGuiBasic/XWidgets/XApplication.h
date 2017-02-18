#pragma once
#include "XWindowsDefines.h"
#include <XAutoPointer.h>

class XApplication
{
public:
    XApplication();
    ~XApplication();
    static HINSTANCE getCurrentHInstance();
    static void setHInstance(HINSTANCE hInstance);
    void run();
private:
    static HINSTANCE hInstance;
};

