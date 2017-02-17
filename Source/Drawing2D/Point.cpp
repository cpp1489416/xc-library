#include "Point.h"
#include "Size.h"

namespace XC
{
    namespace Drawing2D
    {
        class Point::IMPL
        {
        public:
            IMPL(int x = 0, int y = 0) : mX(x), mY(y) {}

        public:
            int mX;
            int mY;
        };

        Point::Point()
        {
        }

        Point::Point(int x, int y) :
            mIMPL(new IMPL(x, y))
        {
        }

        Point::~Point()
        {
            delete mIMPL.Get();
        }

        const int & Point::GetX() const
        {
            return mIMPL->mX;
        }

        void Point::SetX(const int & value)
        {
            mIMPL->mX = value;
        }

        const int & Point::GetY() const
        {
            return mIMPL->mY;
        }

        void Point::SetY(const int & value)
        {
            mIMPL->mY = value;
        }

        Point::operator Size() const
        {
            return Size(GetX(), GetY());
        }
    }
}