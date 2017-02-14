#pragma once

#include "Containers/Queue.h"

namespace XC
{
    namespace Details
    {
        struct Traits
        {

        };
    }


    template <typename TFunction>
    class Delegate
    {
    public:
        virtual void Add() {}
        virtual void Invoke() {}    
    };


    namespace Details
    {

    }
}