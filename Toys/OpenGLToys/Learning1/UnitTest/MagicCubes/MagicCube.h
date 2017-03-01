#pragma once 

#include "MagicInsideCube.h"
#include "RotationState.h"
#include "CubeArray.h"

namespace MagicCubes
{
    class MagicCube : public Thing
    {
    public:
        MagicCube();

    public:
        MagicInsideCube * GetInsideCube(int x, int y, int z);
        const RotationState & GetRotationState() & { return mRotationState; }
        void SetRotationState(const RotationState & rotationState);
        bool IsFinishedRotation() const { return mRotationState.IsFinished(); }

        void Update();

    public:
        void OnCreate() override;
        void OnDraw() override;
        void OnChangeTechnique(Technique *technique) {}

    private:
        void InitializeInsideCubes();
        void DestoryInsideCubes();

    private:
        static const int mCountRows = 4; // static for easy code

    private:
        CubeArray mInsideCubes = CubeArray(mCountRows);
        bool mFinishedRotation = true;
        RotationState mRotationState;
     };
}