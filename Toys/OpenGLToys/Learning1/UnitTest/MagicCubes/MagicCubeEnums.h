#pragma once

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
}