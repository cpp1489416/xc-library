#pragma once

#include "../SyntaxSugars/SyntaxSugars.h"

XC_BEGIN_NAMESPACE_2(XC, Functors)
{
    template <typename T>
    class Less
    {
    public:
        bool operator () (const T & a, const T & b)
        {
            return a < b;
        }
    };

} XC_END_NAMESPACE_2