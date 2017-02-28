#pragma once

namespace MagicCube
{
    enum class Direction : int
    {
        Front = 0, Back, Left, Right, Up, Down,
    };

    enum class Color : int
    {
        White = 0, Green, Yellow, Blue, Red, Orange, Black,
    };

    enum class Face : int
    {
        Front, Right, Up,
    };

    enum class Clockwise
    {
        CW, CCW
    };
}