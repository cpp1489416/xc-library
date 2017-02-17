#include "Rectangle.h"
#include "Point.h"
#include "Size.h"

namespace XC
{
    namespace Drawing2D
    {
        class Rectangle::IMPL
        {
        public:
            IMPL(double x = 0, double y = 0, double width = 0, double height = 0) :
                mX(x), mY(y), mWidth(width), mHeight(height)
            {
            }

        public:
            double mX;
            double mY;
            double mWidth;
            double mHeight;
        };

        Rectangle::Rectangle()
        {
        }

        Rectangle::Rectangle(double x, double y, double width, double height) :
            mIMPL(new IMPL(x, y, width, height))
        {
        }

        Rectangle::~Rectangle()
        {
            delete mIMPL.Get();
        }

        const double & Rectangle::GetX() const
        {
            return mIMPL->mX;
        }

        void Rectangle::SetX(const double & value)
        {
            mIMPL->mX = value;
        }

        const double & Rectangle::GetY() const
        {
            return mIMPL->mY;
        }

        void Rectangle::SetY(const double & value)
        {
            mIMPL->mY = value;
        }

        const double & Rectangle::GetWidth() const
        {
            return mIMPL->mWidth;
        }

        void Rectangle::SetWidth(const double & value)
        {
            mIMPL->mWidth = value;
        }

        const double & Rectangle::GetHeight() const
        {
            return mIMPL->mHeight;
        }

        void Rectangle::SetHeight(const double & value)
        {
            mIMPL->mHeight = value;
        }
    }
};