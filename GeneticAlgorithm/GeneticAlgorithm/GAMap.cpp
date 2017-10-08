#include "GAMap.h"

namespace GA
{
    Map::Map(int width, int height)
    {
    }

    Map::Map(int width, int height)
    {
        mMap.resize(height);
        for (int r = 0; r < height; r++)
        {
            mMap[r].resize(width);
            for (int c = 0; c < width; c++)
            {
                mMap[r][c] = Dot::Road;
            }
        }
    }

    Map::~Map()
    {

    }
}

