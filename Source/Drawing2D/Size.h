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
            Size(int x, int y);
            ~Size();

        public:
            const int & GetWidth() const;
            void SetWidth(const int & value);
            const int & GetHeight() const;
            void SetHeight(const int & value);

            operator Point () const;

        private:
            class IMPL;
            IMPLPointer<IMPL> mIMPL;
        };
    }
}