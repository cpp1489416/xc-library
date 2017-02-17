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
            IMPL(int x = 0, int y = 0, int width = 0, int height = 0) :
                mX(x), mY(y), mWidth(width), mHeight(height)
            {
            }

        public:
            int mX;
            int mY;
            int mWidth;
            int mHeight;
        };

        Rectangle::Rectangle()
        {
        }

        Rectangle::Rectangle(int x, int y, int width, int height) :
            mIMPL(new IMPL(x, y, width, height))
        {
        }

        Rectangle::~Rectangle()
        {
            delete mIMPL.Get();
        }

        const int & Rectangle::GetX() const
        {
            return mIMPL->mX;
        }

        void Rectangle::SetX(const int & value)
        {
            mIMPL->mX = value;
        }

        const int & Rectangle::GetY() const
        {
            return mIMPL->mY;
        }

        void Rectangle::SetY(const int & value)
        {
            mIMPL->mY = value;
        }

        const int & Rectangle::GetWidth() const
        {
            return mIMPL->mWidth;
        }

        void Rectangle::SetWidth(const int & value)
        {
            mIMPL->mWidth = value;
        }

        const int & Rectangle::GetHeight() const
        {
            return mIMPL->mHeight;
        }

        void Rectangle::SetHeight(const int & value)
        {
            mIMPL->mHeight = value;
        }
    }
};