#pragma once

#include <Core/Core.h>

XC_BEGIN_NAMESPACE_2(XC, Drawing2D)
{
    class Point
    {
    public:
        Point(float x = 0, float y = 0) : mX(x), mY(y)
        {
        }

        const float& RX() const
        {
            return mX;
        }

        const float& RY() const
        {
            return mY;
        }

        float& RX()
        {
            return mX;
        }

        float& RY()
        {
            return mY;
        }

    private:
        float mX;
        float mY;
    };

    class Size : public Point
    {
    public:
        Size(float width, float height) : Point(width, height)
        {
        }

        const float& RWidth() const 
        {
            return RX();
        }

        const float& RHeight() const
        {
            return RY();
        }

        float& RWidth()
        {
            return RX();
        }

        float& RHeight()
        {
            return RY();
        }
    };

    class Rectangle
    {
    public:
        Rectangle(const Point& start, const Size& size) : mStart(start), mSize(size)
        { 
        }

        const Point& RStart() const
        {
            return mStart;
        }

        const Size& RSize() const 
        {
            return mSize;
        }

        Point& RStart()
        {
            return mStart;
        }

        Size& RSize()
        {
            return mSize;
        }

    private:
        Point mStart;
        Size mSize;
    };

    class Line
    {
    public:
        Line(Point& from, Point& to) : mFrom(from), mTo(to)
        {
        }

        const Point& RFrom() const
        {
            return mFrom;
        }

        const Point& RTo() const
        {
            return mTo;
        }

        Point& RFrom()
        {
            return mFrom;
        }

        Point& RTo() 
        {
            return mTo;
        }

    private:
        Point mFrom;
        Point mTo;
    };

    // Color is just single color
    class Color
    {
    public:
        Color(float red = 1.0f, float green = 1.0f, float blue = 1.0f) : mR(red), mG(green), mB(blue)
        {
        }

        const float& RRed() const
        {
            return mR;
        }

        const float& RGreen() const
        {
            return mG;
        }

        const float& RBlue() const
        {
            return mB;
        }

        const float& RRed()
        {
            return mR;
        }

        float& RGreen()
        {
            return mG;
        }

        float& RBlue()
        {
            return mB;
        }

    private:
        float mR;
        float mG;
        float mB;
    };

    namespace Colors
    {
        /*
        Color White = Color(1.0f, 1.0f, 1.0f);
        Color Black = Color(0.0f, 0.0f, 0.0f);
        Color Red = Color(1.0f, 0.0f, 0.0f);
        Color Green = Color(0.0f, 1.0f, 0.0f);
        Color Blue = Color(0.0f, 0.0f, 1.0f);
    */
    }

    // pen is color plus width
    class Pen
    {
    public:
        Pen(const Color& color = Color(), float width = 1.0f) : mColor(color), mWidth(width)
        {
        }

        const Color& RColor() const
        {
            return mColor;
        }

        const float& RWidth() const
        {
            return mWidth;
        }

        Color& RColor()
        {
            return mColor;
        }

        float& RWidth()
        {
            return mWidth;
        }

    private:
        Color mColor;
        float mWidth;
    };

    // canvas can draw things
    class ICanvas
    {
    public:
        virtual void Clear(const Color& color) = 0;
        virtual void DrawRectangle(const Pen& pen, const Rectangle& rectangle) = 0;
        virtual void DrawCircle(const Pen& pen, const Rectangle& area) = 0;
        virtual void DrawLine(const Pen& pen, const Line& line) = 0;
    };

} XC_END_NAMESPACE_2;