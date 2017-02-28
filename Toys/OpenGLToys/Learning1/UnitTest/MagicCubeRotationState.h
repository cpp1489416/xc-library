#pragma once 
#pragma once

#include "MagicCubeEnums.h"
#include "glm/matrix.hpp"

namespace MagicCube
{
    class MagicCube;

    class RotationState
    { 
    public:
        RotationState(Face face = Face::Front, Clockwise clockwise = Clockwise::CCW, int lineIndex = 0, int times = 1) :
            mFace(face), mClockwise(clockwise), mLineIndex(lineIndex), mTimes(times) {}

        RotationState & operator = (const RotationState &) = default;

    public:
        bool IsFinished() const { return mFinished; }
        Face GetFace() const { return mFace; }
        Clockwise GetClockwise() const { return mClockwise; }
        int GetLineIndex() const { return mLineIndex; }
        int GetTimes() const { return mTimes; }
        glm::mat4 GetRotationMatrix() const;

    private:
        Face mFace;
        Clockwise mClockwise;
        int mLineIndex;
        int mTimes;
        bool mFinished = false;

        friend class MagicCube;
    };
}