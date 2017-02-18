#ifndef XRectangle_H
#define XRectangle_H

#include "XPoint.h"
#include "XSize.h"

class XRectangle
{
public:
    XRectangle(xreal x = 0.0, xreal y = 0.0, xreal width = 0.0, xreal height = 0.0)
        : x(x), y(x), width(width), height(height) {}

    XRectangle(const XPoint & start, const XSize & size)
    {
        x = start.getX();
        y = start.getY();
        width = size.getWidth();
        height = size.getHeight();
    }

    inline void setStart(const XPoint & start)
    {
        x = start.getX();
        y = start.getY();
    }

    inline void setSize(const XSize & size)
    {
        width = size.getWidth();
        height = size.getHeight();
    }

    inline xreal & rX() { return x; }
    inline xreal & rY() { return y; }
    inline xreal & rWidth() { return width; }
    inline xreal & rHeight() { return height; }
    inline xreal getX() const { return x; }
    inline xreal getY() const { return y; }
    inline xreal getWidth() const { return width; }
    inline xreal getHeight() const { return height; }
    inline XPoint getStart() const { return XPoint(x, y); }
    inline XSize getSize() const { return XSize(width, height); }

    inline bool isInMe(const XPoint & point)
    {
        return point.getX() >= x
            && point.getY() >= y
            && point.getX() <= x + width
            && point.getY() <= y + height;
    }

    inline bool isInMe(const XRectangle & rectangle)
    {
        return x <= rectangle.getX()
            && y <= rectangle.getY()
            && x + width <= rectangle.getX() + rectangle.getWidth()
            && y + height <= rectangle.getY() + rectangle.getHeight();
    }

private:
    xreal x;
    xreal y;
    xreal width;
    xreal height;
};

#endif

