#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"

XC_BEGIN_NAMESPACE_2(XC, Functors)
{
    template <typename TArgument, typename TResult>
    class UnaryFunctor
    {
    public:
        using ArgumentType = TArgument;
        using ResultType = TResult;
    };

    template <typename TArgument1, typename TArgument2, typename TResult>
    class BinaryFunctor
    {
    public:
        using FirstArgumentType = TArgument1;
        using SecondArgumentType = TArgument2;
        using ResultType = TResult;
    };

    template <typename T>
    class Negate : public UnaryFunctor<T, T>
    {
    public:
        T operator () (const T& x) const
        {
            return -x;
        }
    };

    template <typename T>
    class Plus : public BinaryFunctor<T, T, T>
    {
    public:
        T operator () (const T& x, const T& y) const
        {
            return x + y;
        }
    };

    template <typename T>
    class Minus : public BinaryFunctor<T, T, T>
    {
    public:
        T operator () (const T& x, const T& y) const
        {
            return x - y;
        }
    };

    template <typename T>
    class Multiply : public BinaryFunctor<T, T, T>
    {
    public:
        T operator () (const T& x, const T& y) const
        {
            return x * y;
        }
    };

    template <typename T>
    class Divide : public BinaryFunctor<T, T, T>
    {
    public:
        T operator () (const T&x, const T& y)
        {
            return x / y;
        }
    };

    template <typename T>
    class Modulus : public BinaryFunctor<T, T, T>
    {
    public:
        T operator () (const T& x, const T& y) const
        {
            return x % y;
        }
    };

    template <typename T>
    class Less : public BinaryFunctor<T, T, bool>
    {
    public:
        bool operator () (const T& x, const T& y) const
        {
            return x < y;
        }
    };

    template <typename T>
    class Greater : public BinaryFunctor<T, T, bool>
    {
    public:
        bool operator () (const T& x, const T& y) const
        {
            return x > y;
        }
    };

    template <typename T>
    class EqualTo : public BinaryFunctor<T, T, bool>
    {
    public:
        bool operator () (const T& x, const T& y) const
        {
            return x == y;
        }
    };

    template <typename T>
    class NotEqualTo : public BinaryFunctor<T, T, bool>
    {
    public:
        bool operator () (const T& x, const T& y) const
        {
            return x != y;
        }
    };

} XC_END_NAMESPACE_2;