#pragma once

#include "../Core/Property.h"
#include "../Core/Pointers/IMPLPointer.h"

namespace XC
{
    namespace Drawing2D
    {
        class Size;

        class Point
        {
        public:
            Point();
            Point(double x, double y);
            ~Point();

        public:
            const double & GetX() const;
            void SetX(const double & value);
            const double & GetY() const;
            void SetY(const double & value);

            operator Size() const;

        private:
            class IMPL;
            IMPLPointer<IMPL> mIMPL;
        };
    }
}