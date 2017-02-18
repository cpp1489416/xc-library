// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <XRectangle.h>
#include <iostream>

using namespace std;

class A
{
    A()
    {
        xPause();
    }
};

int main()
{
    xPause();
    XRectangle rect;

    cout << rect.getHeight();
    system("Pause");
    return 0;
}

