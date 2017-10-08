#pragma once

#include <memory>

#include "UniquePointer.h"
#include "IMPLPointer.h"
#include "ValuePointer.h"

namespace XC
{
    template <typename T>
    using Pointer = std::shared_ptr<T>;
}