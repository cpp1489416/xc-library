#pragma once

#define XC_DELETE_IMPL(iMPL) delete iMPL.Get();

namespace XC
{
    template <typename T>
    class IMPLPointer
    {
    public:
        using Self = IMPLPointer<T>;

    public:
        IMPLPointer()
        {
            mValue = new T();
        }

        IMPLPointer(T * value) :
            mValue(value)
        {
        }

        IMPLPointer(const Self & rhs)
        {
            mValue = new T(*rhs.mValue);
        }

        Self & operator = (const Self & rhs)
        {
            delete mValue;
            mValue = new T(*rhs.mValue);
        }

    public:
        T * Get() const
        {
            return mValue;
        }

        T * operator -> () const
        {
            return mValue;
        }

        operator T * () const
        {
            return mValue;
        }
        
    private:
        T * mValue;
    };
}