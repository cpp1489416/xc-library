#include "Size.h"
#include "Point.h"

namespace XC
{
    namespace Drawing2D
    {
        class Size::IMPL
        {
        public:
            IMPL(double width = 0, double height = 0) : mWidth(width), mHeight(height) {}

        public:
            double mWidth;
            double mHeight;
        };

        Size::Size()
        {
        }

        Size::Size(double width, double height) :
            mIMPL(new IMPL(width, height))
        {
        }

        Size::~Size()
        {
            delete mIMPL.Get();
        }

        const double & Size::GetWidth() const
        {
            return mIMPL->mWidth;
        }

        void Size::SetWidth(const double & value)
        {
            mIMPL->mWidth = value;
        }

        const double & Size::GetHeight() const
        {
            return mIMPL->mHeight;
        }

        void Size::SetHeight(const double & value)
        {
            mIMPL->mHeight = value;
        }

        Size::operator Point() const
        {
            return Point(GetWidth(), GetHeight());
        }
    }
}