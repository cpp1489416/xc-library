#pragma once 

#include "MagicInsideCube.h"
#include "RotationState.h"
#include "CubeArray.h"
#include <qtimer.h>

namespace MagicCubes
{
    class MagicCube : public QObject, public Thing
    {
        Q_OBJECT

    public: signals :
        void UpdatedSignal();

    public:
        MagicCube();

    public:
        MagicInsideCube * GetInsideCube(int x, int y, int z);
        int GetCountRows() const { return mCountRows; }
        void RequireRotationState(const RotationState & rotationState);
        const RotationState & GetRotationState() & { return mRotationState; }
        bool IsRotationFinished() const { return mRotationState.IsFinished(); }
        void Update();

    public:
        void OnCreate() override;
        void OnDraw() override;
        void OnChangeTechnique(Technique * technique) {}

    public:
        TimeoutEventHandler TimeoutEvent;

    private:
        void InitializeInsideCubes();
        void DestoryInsideCubes();
        void StartRoatation();
        void UpdateRotation();
        void FinishRotation();
        void OnTimeout();

    private:
        static const int mCountRows = 4; // static for easy code

    private:
        QTimer * mTimer;
        CubeArray mInsideCubes = CubeArray(mCountRows);
        RotationState mRotationState;
        bool mRotationFinished = true;
        double mCurrentRotationRadius;
        double mRotationFinishedRadius;
        const double mDeltaRadius = 0.01f;
        glm::mat4 mRotationMatrix;
    };
}