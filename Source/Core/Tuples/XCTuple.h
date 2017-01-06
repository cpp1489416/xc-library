
#ifndef XCTUPLES_H
#define XCTUPLES_H

#include "../XCBasic.h"

namespace XC
{
    template <typename ... TList> class Tuple;

    template <>
    class Tuple<>
    {
    public:
        typedef Tuple<> ValueType;

        Tuple() {}

        static const xsize mSize = 0;
    };

    template <typename T>
    class Tuple<T>
    {
    public:
        typedef T ThisType;
        typedef Tuple<> BaseType;

        Tuple() {}

        template <typename T2>
        Tuple(const T2 & value) : mValue(value) {}

        template <typename T2>
        Tuple(const Tuple<T2> & rhs) : mValue(rhs.mValue) {}

        template <typename T2>
        Tuple<T> & operator = (const Tuple<T> & rhs) 
        {
            mValue = rhs.mValue;
            return *this; 
        }

        const T & GetFirst() const { return mValue; }
        T & GetFirst() { return mValue; }
        const BaseType & GetBase() const { return static_cast<const BaseType &>(*this); }
        BaseType & GetBase() { return static_cast<BaseType &>(*this); }
        
        static const xsize mSize = 1;
        T mValue;
    };

    template <typename TFirst, typename ... TRest>
    class Tuple<TFirst, TRest ...> : public Tuple<TRest ...>
    {
    public:
        typedef Tuple<TFirst, TRest ...> Self;
        typedef Tuple<TRest ...> BaseType;

        Tuple() {}

        template <typename TFirst2, typename ... TRest2>
        Tuple(const TFirst2 & value, const TRest2 & ... rest)
            : BaseType(rest ...), mValue(value) {} // BaseType will be initialized first if

        template <typename TFirst2, typename ... TRest2>
            Tuple(const TFirst2 & value, const Tuple<TRest2 ...> & rest)
            : BaseType(rest), mValue(value) {}

        template <typename ... TList>
            Tuple(const Tuple<TList ...> & rhs)
            : mValue(rhs.mValue) { GetBase() = rhs.GetBase(); }

        template <typename TFirst2, typename ... TRest2>
            Self & operator = (const Tuple<TFirst2, TRest2 ...> & rhs)
        {
            GetBase() = rhs.GetBase();
            mValue = rhs.mValue; 
            return *this;
        }

        const TFirst & GetFirst() const { return mValue; }
        TFirst & GetFirst() { return mValue; }
        const BaseType & GetBase() const { return static_cast<const BaseType &>(*this); }
        BaseType & GetBase() { return static_cast<BaseType &>(*this); }

        static const xsize mSize = 1 + BaseType::mSize;
        TFirst mValue;
    };

    namespace Tuples
    {
        namespace Detail
        {
            template <xsize TIndex, typename ... TList> class TupleAt;
            
            template <xsize TIndex, typename TFirst, typename ... TRest>
            class TupleAt<TIndex, Tuple<TFirst, TRest ...> >
            {
            public:
                typedef typename TupleAt<TIndex - 1, Tuple<TRest ...> >::ValueType ValueType;
                typedef typename TupleAt<TIndex - 1, Tuple<TRest ...> >::TupleType TupleType;
            };

            template <typename TFirst, typename ... TRest>
            class TupleAt<0, Tuple<TFirst, TRest ...> >
            {
            public:
                typedef TFirst ValueType;
                typedef Tuple<TFirst, TRest ...> TupleType;
            };

            template <>
            class TupleAt<0, Tuple<> >
            {
            public:
                typedef Tuple<> ValueType;
                typedef Tuple<> TupleType;
            };
        }

        template <xsize TIndex, typename ... TList>
        const typename Detail::TupleAt<TIndex, Tuple<TList ...> >::ValueType &
            Get(const Tuple<TList ...> & tuple);

        template <xsize TIndex, typename ... TList>
        typename Detail::TupleAt<TIndex, Tuple<TList ...> >::ValueType & Get(Tuple<TList ...> & tuple);
        
        template <typename ... TList>
        Tuple<TList ...> MakeTuple(TList ...);
    }

    namespace Tuples
    {
        template <xsize TIndex, typename ... TList>
        const typename Detail::TupleAt<TIndex, Tuple<TList ...> >::ValueType &
            Get(const Tuple<TList ...> & tuple)
        {
            typedef Tuple<TList ...> TupleType;
            typedef typename Detail::TupleAt<TIndex, TupleType>::TupleType BaseTupleType;
            return static_cast<const BaseTupleType &>(tuple).GetFirst();
        }

        template <xsize TIndex, typename ... TList>
        typename Detail::TupleAt<TIndex, Tuple<TList ...> >::ValueType & Get(Tuple<TList ...> & tuple)
        {
            typedef Tuple<TList ...> TupleType;
            typedef typename Detail::TupleAt<TIndex, TupleType>::TupleType BaseTupleType;
            return static_cast<BaseTupleType &>(tuple).GetFirst();
        }

        template <typename T>
        Tuple<T> MakeTuple(T value)
        {
            return Tuple<T>(value);
        }

        template <typename TFirst, typename ... TRest>
        Tuple<TFirst, TRest ...> MakeTuple(TFirst first, TRest ... rest)
        {
            return Tuple<TFirst, TRest ...>(first, rest...);
        }
    }
}

#endif // XCTUPLES_H
