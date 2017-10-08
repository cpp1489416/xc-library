#pragma once

#ifndef XC_CORE_TYPES_TYPES_H
#define XC_CORE_TYPES_TYPES_H

#include "../SyntaxSugars/SyntaxSugars.h"
#include "Basic.h"
#include "TypeTraits.h"

XC_BEGIN_NAMESPACE_2(XC, Types)
{
    XC_BEGIN_NAMESPACE_1(Details)
    {
        static inline bool IsPlainOldData(TrueTraitType)
        {
            return true;
        }

        static inline bool IsPlainOldData(FalseTraitType)
        {
            return false;
        }

    } XC_END_NAMESPACE_1;

    template <typename T>
    bool IsPlainOldData(T)
    {
        return Details::IsPlainOldData(TypeTraits<T>::IsPlainOldDataType());
    }

} XC_END_NAMESPACE_2

/*
#include <iostream>
class Ad
{
public:

private:

};


template <> class XC::TypeTraits<Ad>
{
public:
    using IsPlainOldDataType = typename XC::TrueTraitType;
};

XC_TEST_CASE(PLAINOLDATETEST)
{
    

    std::cout << XC::Types::IsPlainOldData(Ad()) << " A plain old dat\n";
    std::cout << XC::Types::IsPlainOldData(423) << " int plain old data\n";
}
*/


#endif // XC_CORE_TYPES_TYPES_H 