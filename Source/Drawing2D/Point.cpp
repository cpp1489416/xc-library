#include "Point.h"
#include "Size.h"

namespace XC
{
    namespace Drawing2D
    {
        class Point::IMPL
        {
        public:
            IMPL(double x = 0, double y = 0) : mX(x), mY(y) {}

        public:
            double mX;
            double mY;
        };

        Point::Point()
        {
        }

        Point::Point(double x, double y) :
            mIMPL(new IMPL(x, y))
        {
        }

        Point::~Point()
        {
            delete mIMPL.Get();
        }

        const double & Point::GetX() const
        {
            return mIMPL->mX;
        }

        void Point::SetX(const double & value)
        {
            mIMPL->mX = value;
        }

        const double & Point::GetY() const
        {
            return mIMPL->mY;
        }

        void Point::SetY(const double & value)
        {
            mIMPL->mY = value;
        }

        Point::operator Size() const
        {
            return Size(GetX(), GetY());
        }
    }
}