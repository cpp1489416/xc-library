#pragma once

#include "../Core/Property.h"
#include "../Core/Pointers/IMPLPointer.h"

namespace XC
{
    namespace Drawing2D
    {
        class Point;

        class Size
        {
        public:
            Size();
            Size(double x, double y);
            ~Size();

        public:
            const double & GetWidth() const;
            void SetWidth(const double & value);
            const double & GetHeight() const;
            void SetHeight(const double & value);

            operator Point () const;

        private:
            class IMPL;
            IMPLPointer<IMPL> mIMPL;
        };
    }
}