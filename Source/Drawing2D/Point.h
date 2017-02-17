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
            Point(int x, int y);
            ~Point();

        public:
            const int & GetX() const;
            void SetX(const int & value);
            const int & GetY() const;
            void SetY(const int & value);

            operator Size() const;

        private:
            class IMPL;
            IMPLPointer<IMPL> mIMPL;
        };
    }
}