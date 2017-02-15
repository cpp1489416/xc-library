#pragma once

#include "Delegate.h"

namespace XC
{
    template <typename T>
    class Property
    {
    public:
        using Self = Property<T>;
        using GetEventHandler = Delegate<const T &>;
        using SetEventHandler = Delegate<void, const T &>;

    public:
        template <typename TClassType>
        void Create(TClassType * className, const T & (TClassType::*getFunction)() const, void (TClassType::*setFunction)(const T & value))
        {
            mGet.RemoveAll();
            mSet.RemoveAll();

            mGet.Add(className, getFunction);
            mSet.Add(className, setFunction);
        }

        const T & Get() const
        {
            return mGet.Invoke();
        }

        void Set(const T & value)
        {
            mSet.Invoke(value);
        }

        operator const int & () const
        {
            return Get();
        }

        Self & operator = (const T & value)
        {
            Set(value);
            return *this;
        }

    private:
        GetEventHandler mGet;
        SetEventHandler mSet;
    };
}