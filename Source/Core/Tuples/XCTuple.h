
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
        Tuple(T2 value) : mValue(value) {}
       
        static const xsize mSize = 1;
        T mValue; 
    };

    template <typename TFirst, typename ... TRest>
    class Tuple<TFirst, TRest ...> : public Tuple<TRest ...>
    {
    public:
        typedef TFirst ThisType;
        typedef Tuple<TRest ...> BaseType;

        Tuple() {}

        template <typename TFirst2, typename ... TRest2>
        Tuple(const TFirst2 & value, const TRest2 & ... rest) : mValue(value), BaseType(rest ...) {}

        static const xsize mSize = 1 + BaseType::mSize;
        TFirst mValue;
    };

    namespace Tuples
    {
        namespace IMPL
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
                typedef Tuple<> TypleType;
            };
        }

        template <xsize TIndex, typename ... TList>
        const typename IMPL::TupleAt<TIndex, Tuple<TList ...> >::ValueType &
            Get(const Tuple<TList ...> & tuple)
        {
            typedef Tuple<TList ...> TupleType;
            typedef typename IMPL::TupleAt<TIndex, TupleType>::TupleType BaseTupleType;
            return static_cast<const BaseTupleType &>(tuple).mValue;
        }

        template <xsize TIndex, typename ... TList>
        typename IMPL::TupleAt<TIndex, Tuple<TList ...> >::ValueType & Get(Tuple<TList ...> & tuple)
        {
            typedef Tuple<TList ...> TupleType;
            typedef typename IMPL::TupleAt<TIndex, TupleType>::TupleType BaseTupleType;
            return static_cast<BaseTupleType &>(tuple).mValue;
        }

    }
}

#endif // XCTUPLES_H
