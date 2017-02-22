#pragma once

#include "../../Core/Core.h"

XC_BEGIN_NAMESPACE_2(XC, GUI)
{
    class EventArguments
    {
    public:
    };

    using EventHandler = Delegate<void, Object, EventArguments>;
    
} XC_END_NAMESPACE_2