#include "stdafx.h"
#include "XVector.h"
#include "XGlobal.h"
#include <vector>
#include <iostream>
#include "XSize.h"
#include "XSignal.h"

using namespace std;

class Widget
{
public:
    void doEvent()
    {
        signal.emit();
    }

    XSignal signal;
};

class SlotProvider
{
public:
    inline void onSignal()
    {
        cout << "haha my RussiaWidget!\n";
    }

    inline void onSignal2()
    {
        cout << "this is the second Signal!!!\n";
    }
};   


class RussiaWidget
{
public:
    RussiaWidget()
    {
        widget.signal.connect(this, &RussiaWidget::onSignal);
    }


    void resetSignal(int num)
    {
        if (num == 0)
        {
            widget.signal.connect(&provider, &SlotProvider::onSignal);
        }
        else if (num == 1)
        {
            widget.signal.connect(&provider, &SlotProvider::onSignal2);
        }
        else if (num == 3)
        {
            widget.signal.connect(onSignal3);
        }
        else
        {
            widget.signal.disconnect();
        }
    }

    void doEvent()
    {
        widget.doEvent();
    }

private:
    inline void onSignal()
    {
        cout << "haha my RussiaWidget!\n";
    }

    inline void onSignal2()
    {
        cout << "this is the second Signal!!!\n";
    }


    static void onSignal3()
    {
        cout << "this is a static Signal!!! i am genius!\n";
    }

    Widget widget;
    SlotProvider provider;
};

int main()
{
    RussiaWidget widget;
    widget.doEvent();
    widget.resetSignal(1);
    widget.doEvent();
    widget.resetSignal(2);
    widget.doEvent();
    widget.resetSignal(3);
    widget.doEvent();
    xPause();    
    
    return 0;
}