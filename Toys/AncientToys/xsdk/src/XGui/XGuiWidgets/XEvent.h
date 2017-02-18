#ifndef XEVENT_H
#define XEVENT_H

class XEvent
{
public:
    XEvent();
    ~XEvent();
};

class XPaintEvent : public XEvent
{
public:

private:

};

class XKeyEvent : public XEvent
{


};

class XSizeEvent : public XEvent
{
public:
    XSizeEvent(int width = 0, int height = 0)
        : width(width), height(height)
    {
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

private:
    int width;
    int height;
};

typedef XSizeEvent XMouseEvent;
#endif