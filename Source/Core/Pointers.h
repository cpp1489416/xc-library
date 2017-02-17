#pragma once

#include "Pointers/UniquePointer.h"
#include "Pointers/IMPLPointer.h"

namespace XC
{
    template <typename T>
    using Pointer = ValuePointer<T>
}