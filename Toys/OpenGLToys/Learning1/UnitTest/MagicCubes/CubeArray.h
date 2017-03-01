#pragma once

#include "MagicInsideCube.h"
#include "RotationState.h"
#include <vector>

namespace MagicCubes
{
    class CubeArray
    {
    public:
        CubeArray(int countRows);
        CubeArray(const CubeArray &) = default;
        ~CubeArray() = default;

    public:
        int GetCountRows() const { return mArray.size(); }
        std::vector<std::vector<MagicInsideCube *> > & operator [] (int index) { return mArray[index]; }
        void Rotate(const RotationState & rotationState);

    private:
        CubeArray & operator = (const CubeArray &) = default; // private for easy code
        void RotateCounterClockwiseOneTime(Face face, int arrayIndex); // this function is base on array rotation, 3D rotation is not counted;

    private:
        std::vector<std::vector<std::vector<MagicInsideCube *> > > mArray;
    };
}