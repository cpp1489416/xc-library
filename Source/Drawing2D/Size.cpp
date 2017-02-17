#include "Size.h"
#include "Point.h"

namespace XC
{
    namespace Drawing2D
    {
        class Size::IMPL
        {
        public:
            IMPL(int width = 0, int height = 0) : mWidth(width), mHeight(height) {}

        public:
            int mWidth;
            int mHeight;
        };

        Size::Size()
        {
        }

        Size::Size(int width, int height) :
            mIMPL(new IMPL(width, height))
        {
        }

        Size::~Size()
        {
            delete mIMPL.Get();
        }

        const int & Size::GetWidth() const
        {
            return mIMPL->mWidth;
        }

        void Size::SetWidth(const int & value)
        {
            mIMPL->mWidth = value;
        }

        const int & Size::GetHeight() const
        {
            return mIMPL->mHeight;
        }

        void Size::SetHeight(const int & value)
        {
            mIMPL->mHeight = value;
        }

        Size::operator Point() const
        {
            return Point(GetWidth(), GetHeight());
        }
    }
}