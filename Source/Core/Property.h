#pragma once

namespace XC
{
    namespace Details
    {
        template <typename TClassName, typename TFunction>
        class Delegate
        {
        public:
        };
    }

    template <typename T>
    class Property
    {
    public:
        const T & Get();
        void Set(const T & value);

        T & operator = (const T & value);
        T operator();
    };
    
    template<typename T>
    inline const T & Property<T>::Get()
    {
        return T();
    }
    
    template<typename T>
    inline void Property<T>::Set(const T & value)
    {
    }
    
    template<typename T>
    inline T & Property<T>::operator=(const T & value)
    {
        Set(value);
        return *this;
    }
}