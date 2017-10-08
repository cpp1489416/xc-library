#include "CubeArray.h"

namespace MagicCubes
{
    CubeArray::CubeArray(int countRows)
    {
        for (int i = 0; i < countRows; ++i)
        {
            mArray.push_back(std::vector<std::vector<MagicInsideCube *> >());
            for (int j = 0; j < countRows; ++j)
            {
                mArray[i].push_back(std::vector<MagicInsideCube *>());
                for (int k = 0; k < countRows; ++k)
                {
                    mArray[i][j].push_back(new MagicInsideCube());
                }
            }
        }
    }

    void CubeArray::Rotate(const RotationState & rotationState)
    {
        switch (rotationState.GetFace())
        {
        case Face::Front:
        {
            int times = rotationState.GetTimes();
            if (rotationState.GetClockwise() == Clockwise::CW)
            {
                times = 4 - times;
            }

            while (times--)
            {
                RotateCounterClockwiseOneTime(Face::Front, rotationState.GetLineIndex());
            }

            break;
        }
        case Face::Up:
        {
            int times = rotationState.GetTimes();
            if (rotationState.GetClockwise() == Clockwise::CW)
            {
                times = 4 - times;
            }

            times %= 4;
            
            while (times--)
            {
                RotateCounterClockwiseOneTime(Face::Up, GetCountRows() - 1 - rotationState.GetLineIndex());
            }

            break;
        }
        case Face::Right:
        {
            int times = 4 - rotationState.GetTimes();
            if (rotationState.GetClockwise() == Clockwise::CW)
            {
                times = 4 - times;
            }

            times %= 4;
            
            while (times--)
            {
                RotateCounterClockwiseOneTime(Face::Right, GetCountRows() - 1 - rotationState.GetLineIndex());
            }

            break;
        }
        default:
            break;
        }

    }

    void CubeArray::RotateCounterClockwiseOneTime(Face face, int arrayIndex)
    {
        CubeArray newArray = *this; // operator = is private

        for (int i = 0; i < GetCountRows(); ++i)
        {
            for (int j = 0; j < GetCountRows(); ++j)
            {
                switch (face)
                {
                case MagicCubes::Face::Front:
                    newArray[i][j][arrayIndex] = (*this)[j][GetCountRows() - 1 - i][arrayIndex];
                    break;
                case MagicCubes::Face::Up:
                    newArray[i][arrayIndex][j] = (*this)[j][arrayIndex][GetCountRows() - 1 - i];
                    break;
                case MagicCubes::Face::Right:
                    newArray[arrayIndex][i][j] = (*this)[arrayIndex][j][GetCountRows() - 1 - i];
                    break;
                default:
                    break;
                }
            }
        }

        *this = newArray;
    }
}