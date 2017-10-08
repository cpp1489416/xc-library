#pragma once

#include "../Include/XC/Core/Delegate.h"

namespace MagicCubes
{
    enum class Direction : int
    {
        Right, Left, Up, Down, Back, Front,
    };

    enum class Color : int
    {
        White = 0, Green, Yellow, Blue, Red, Orange, Black,
    };

    enum class Face : int
    {
        Front = 0, Right, Up,
    };

    enum class Clockwise
    {
        CW, CCW
    };

    using TimeoutEventHandler = XC::Delegate<void>;
}