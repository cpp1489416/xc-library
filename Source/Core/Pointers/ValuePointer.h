#pragma once

namespace XC
{
    template <typename T>
    class ValuePointer
    {
    public:
        using Self = ValuePointer<T>;

    public:
        ValuePointer()
        {
            mValue = new T();
        }

        ValuePointer(T * value) :
            mValue(value)
        {
        }

        ValuePointer(const Self & rhs)
        {
            mValue = new T(*rhs.mValue);
        }

        ~ValuePointer()
        {
            delete mValue;
        }

        Self & operator = (const Self & rhs)
        {
            delete mValue;
            mValue = new T(*rhs.mValue);
        }

    public:
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