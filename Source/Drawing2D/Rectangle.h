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
            Rectangle(int x, int y, int width, int height);
            ~Rectangle();

        public:
            const int & GetX() const;
            void SetX(const int & value);
            const int & GetY() const;
            void SetY(const int & value);
            const int & GetWidth() const;
            void SetWidth(const int & value);
            const int & GetHeight() const;
            void SetHeight(const int & value);
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