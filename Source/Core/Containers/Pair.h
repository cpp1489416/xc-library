#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"

XC_BEGIN_NAMESPACE_2(XC, Containers)
{
    template <typename T1, typename T2>
    class Pair
    {
    public:
        T1 mFirst;
        T2 mSecond;
    };

    XC_BEGIN_NAMESPACE_1(Details)
    {
        template <typename T1, typename T2>
        class SelectFirst
        {
        public:
            using PairType = Pair<T1, T2>;

        public:
            T2 & operator () (PairType & pair)
            {
                return pair.mFirst;
            }
        };
       
    } XC_END_NAMESPACE_1;

} XC_END_NAMESPACE_2;