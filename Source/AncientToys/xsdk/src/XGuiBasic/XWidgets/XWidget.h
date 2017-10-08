#pragma once

class XWidget
{
public:
    XWidget();
    ~XWidget();
    void show();

protected:
    virtual void onPaint();
};

