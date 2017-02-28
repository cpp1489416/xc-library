#pragma once 

#include "MagicInsideCube.h"

// a magic cube of 4 * 4 * 4;

class MagicCube : Thing
{
public:
    class RotationState
    {
    public:
        enum class Direction : int
        {
            Right, Left, Up, Down,
        };

    public:
        RotationState(Direction direction = Direction::Right, int lineIndex = 0, int times = 1) :
            mDirection(direction), mLineIndex(lineIndex), mTimes(times) {}

    private:
        Direction mDirection;
        int mLineIndex;
        int mTimes;

        friend class MagicCube;
    };

public:
    MagicCube(int countRows);

public:
    MagicInsideCube * GetInsideCube(int x, int y, int z) const;
    void Update() {} // none update for easy code
    bool IsFinishedRotation() const { return mFinishedRotation; }
    void RequsetRotationState(const RotationState & rotationState);

public:
    void OnCreate() override;
    void OnDraw() override;

private:
    void InitializeInsideCubes();
    void DestoryInsideCubes();

private:
    static const int mCountRows = 4; // static for easy code

private:
    MagicInsideCube * mInsideCubes[mCountRows][mCountRows][mCountRows];
    bool mFinishedRotation = true;
};