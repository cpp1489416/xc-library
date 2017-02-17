#pragma once

#include "../Core/Property.h"
#include "../Core/Pointers/IMPLPointer.h"

namespace XC
{
    namespace Drawing2D
    {
        class Point;
        class Size;


        class Rectangle
        {
        public:
            Rectangle();
            Rectangle(double x, double y, double width, double height);
            ~Rectangle();

        public:
            const double & GetX() const;
            void SetX(const double & value);
            const double & GetY() const;
            void SetY(const double & value);
            const double & GetWidth() const;
            void SetWidth(const double & value);
            const double & GetHeight() const;
            void SetHeight(const double & value);
            Point GetLocation() const;
            void SetLocation(const Point & location);
            Size GetSize() const;
            void SetSize(const Size & size);

        private:
            class IMPL;
            IMPLPointer<IMPL> mIMPL;
        };
    }
}