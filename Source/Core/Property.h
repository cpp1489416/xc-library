#pragma once

#include "Delegate.h"

namespace XC
{
    template <typename T>
    class IProperty
    {
    public:
        virtual const T & Get() const = 0;
        virtual T & Reference() = 0;
        virtual void Set(const T &) = 0;
    };

    template <typename T>
    class Property : public IProperty<T>
    {
    public:
        using Self = Property<T>;
        using GetConstantEventHandler = Delegate<const T &>;
        using GetNotConstantEventHandler = Delegate<T &>;
        using GetValueEventHandler = Delegate<T>;
        using SetEventHandler = Delegate<void, const T &>;

    public:
        Property()
        {
        }

        template <typename TClassType>
        Property(TClassType * className, const T & (TClassType::*getConstantFunction)() const, T &(TClassType::*getNotConstantFunction)(), void (TClassType::*setFunction)(const T & value))
        {
            Clear();

            mGetConstant.Add(className, getConstantFunction);
            mGetNotConstant.Add(className, getNotConstantFunction);
            mSet.Add(className, setFunction);
        }

        template <typename TClassType>
        Property(TClassType * className, const T & (TClassType::*getConstantFunction)() const, T &(TClassType::*getNotConstantFunction)())
        {
            Clear();

            mGetConstant.Add(className, getConstantFunction);
            mGetNotConstant.Add(className, getNotConstantFunction);
        }

        template <typename TClassType>
        Property(TClassType * className, const T & (TClassType::*getFunction)() const, void (TClassType::*setFunction)(const T & value))
        {
            Clear();

            mGetConstant.Add(className, getFunction);
            mSet.Add(className, setFunction);
        }

        template <typename TClassType>
        Property(TClassType * className, T & (TClassType::*getFunction)(), void (TClassType::*setFunction)(const T & value))
        {
            Clear();

            mGetNotConstant.Add(className, getFunction);
            mSet.Add(className, setFunction);
        }

        template <typename TClassType>
        Property(TClassType * className, const T & (TClassType::*getFunction)() const)
        {
            Clear();

            mGetConstant.Add(className, getFunction);
        }

        template <typename TClassType>
        Property(TClassType * className, T & (TClassType::*getFunction)())
        {
            Clear();

            mGetNotConstant.Add(className, getFunction);
        }

        template <typename TClassType>
        Property(TClassType *className, void (TClassType::*setFunction)())
        {
            Clear();

            mSet.Add(className, setFunction);
        }

    public:
        void Clear()
        {
            mGetConstant.RemoveAll();
            mGetNotConstant.RemoveAll();
            mGetValue.RemoveAll();
            mSet.RemoveAll();
        }

        const T & Get() const override
        {
            if (IsConstReferenceGetable())
            {
                return mGetConstant.Invoke();
            }
            else
            {
                throw "Constant reference cannot get";
            }
        }

        T & Reference() override
        {
            if (IsReferenceGetable())
            {
                return mGetNotConstant.Invoke();
            }
            else
            {
                throw "Cannot get";
            }
        }

        void Set(const T & value) override
        {
            if (IsSetable())
            {
                mSet.Invoke(value);
            }
            else if (IsReferenceGetable())
            {
                Reference() = value;
            }
            else
            {
                throw "Cannot set";
            }
        }

        bool IsGetable() const
        {
            return IsConstReferenceGetable() || IsReferenceGetable();
        }

        bool IsConstReferenceGetable() const
        {
            return mGetConstant.GetCount() > 0;
        }

        bool IsReferenceGetable() const
        {
            return mGetNotConstant.GetCount() > 0;
        }

        bool IsSetable() const
        {
            return mSet.GetCount() > 0 || IsReferenceGetable();
        }

        operator const T & () const
        {
            return Get();
        }

        Self & operator = (const T & value)
        {
            Set(value);
            return *this;
        }

    private:
        GetConstantEventHandler mGetConstant;
        GetNotConstantEventHandler mGetNotConstant;
        GetValueEventHandler mGetValue;
        SetEventHandler mSet;
    };

    template <typename T>
    class BasicProperty : IProperty<T>
    {
    public:
        using Self = BasicProperty<T>;

    public:
        BasicProperty()
        {
        }

        BasicProperty(const T & value) :
            mValue(value)
        {
        }

    public:
        const T & Get() const override
        {
            return mValue;
        }

        T & Reference() override
        {
            return mValue;
        }

        void Set(const T & value)
        {
            mValue = value;
        }

        operator const T & () const
        {
            return Get();
        }

        Self & operator = (const T & value)
        {
            Set(value);
            return *this;
        }

    private:
        T mValue;
    };
}