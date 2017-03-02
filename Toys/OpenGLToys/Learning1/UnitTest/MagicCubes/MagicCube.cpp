#include "MagicCube.h"
#include "RotationState.h"
#include "../CXCGL/Technique.h"
#include <qtimer.h>

namespace
{
    const double PI = 3.1415;
}

namespace MagicCubes
{
    MagicCube::MagicCube() // count if rows is always 4
    {
        mTimer = new QTimer();
        QObject::connect(mTimer, &QTimer::timeout, this, &MagicCube::OnTimeout);
    }

    MagicInsideCube * MagicCube::GetInsideCube(int x, int y, int z)
    {
        return mInsideCubes[x][y][z];
    }

    void MagicCube::RequireRotationState(const RotationState & rotationState)
    {
        mRotationState = rotationState;
        StartRoatation();
    }

    void MagicCube::Update()
    {
        FinishRotation();
    }

    void MagicCube::OnCreate()
    {
        InitializeInsideCubes();
    }

    void MagicCube::OnDraw()
    {
        glm::mat4 selfModelMatrix = *mTransform.GetMatrix();

        for (int i = 0; i < mCountRows; ++i)
        {
            for (int j = 0; j < mCountRows; ++j)
            {
                for (int k = 0; k < mCountRows; ++k)
                {
                    MagicInsideCube * cube = mInsideCubes[i][j][k];
                    glm::mat4 rotationMatrix = cube->GetRotationMatrix();
                    glm::mat4 modelMatrix = selfModelMatrix * rotationMatrix;// *;

                    if (cube->mInRotation)
                    {
                        modelMatrix = mRotationMatrix * modelMatrix;
                    }

                    glUniformMatrix4fv(mTechnique->GetUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
                    cube->OnDraw();
                }
            }
        }

        //    mInsideCubes[0][0][0]->OnDraw();
    }

    void MagicCube::InitializeInsideCubes()
    {
        for (int i = 0; i < mCountRows; ++i)
        {
            for (int j = 0; j < mCountRows; ++j)
            {
                for (int k = 0; k < mCountRows; ++k)
                {
                    mInsideCubes[i][j][k] = new MagicInsideCube();
                }
            }
        }

        for (int i = 0; i < mCountRows; ++i)
        {
            for (int j = 0; j < mCountRows; ++j)
            {
                // right face is red
                mInsideCubes[mCountRows - 1][i][j]->SetFaceColor(Direction::Right, Color::Red);

                // left face is orange
                mInsideCubes[0][i][j]->SetFaceColor(Direction::Left, Color::Orange);

                // up face is yellow
                mInsideCubes[i][mCountRows - 1][j]->SetFaceColor(Direction::Up, Color::Yellow);

                // down face is white
                mInsideCubes[i][0][j]->SetFaceColor(Direction::Down, Color::White);

                // back face is green 
                mInsideCubes[i][j][mCountRows - 1]->SetFaceColor(Direction::Back, Color::Green);

                // front face is blue
                mInsideCubes[i][j][0]->SetFaceColor(Direction::Front, Color::Blue);
            }
        }

        for (int i = 0; i < mCountRows; ++i)
        {
            for (int j = 0; j < mCountRows; ++j)
            {
                for (int k = 0; k < mCountRows; ++k)
                {
                    mInsideCubes[i][j][k]->Create();
                }
            }
        }

        for (int i = 0; i < mCountRows; ++i)
        {
            for (int j = 0; j < mCountRows; ++j)
            {
                for (int k = 0; k < mCountRows; ++k)
                {
                    MagicInsideCube * cube = mInsideCubes[i][j][k];
                    float xDiff = (i - (mCountRows / 2.0f - 0.5f)) * 3.0f;
                    float yDiff = (j - (mCountRows / 2.0f - 0.5f)) * 3.0f;
                    float zDiff = (k - (mCountRows / 2.0f - 0.5f)) * 3.0f;
                    glm::mat4 translateMatrix = glm::translate(glm::mat4(1), glm::vec3(xDiff, yDiff, zDiff));
                    glm::mat4 rotationMatrix = cube->GetRotationMatrix();
                    glm::mat4 modelMatrix = translateMatrix * rotationMatrix;
                    cube->SetRotationMatrix(modelMatrix);
                }
            }
        }
    }

    void MagicCube::DestoryInsideCubes()
    {
        for (int i = 0; i < mCountRows * mCountRows * mCountRows; ++i)
        {
            delete mInsideCubes[i / mCountRows / mCountRows][(i / mCountRows) % mCountRows][i % mCountRows];
        }
    }

    void MagicCube::StartRoatation()
    {
        mCurrentRotationRadius = 0.0;
        mRotationFinishedRadius = mRotationState.GetTimes() * PI / 2.0;
        mRotationFinished = false;

        // set rotation flags
        for (int i = 0; i < GetCountRows(); ++i)
        {
            for (int j = 0; j < GetCountRows(); ++j)
            {
                int lineIndex = mRotationState.GetLineIndex();
                switch (mRotationState.GetFace())
                {
                case Face::Right:
                    mInsideCubes[GetCountRows() - 1 - lineIndex][i][j]->mInRotation = true;
                    break;
                case Face::Up:
                    mInsideCubes[i][GetCountRows() - 1 - lineIndex][j]->mInRotation = true;
                    break;
                case Face::Front:
                    mInsideCubes[i][j][lineIndex]->mInRotation = true;
                    break;
                default:
                    break;
                }
            }
        }

        mRotationMatrix = glm::mat4(1);
        mTimer->start(10);
    }

    void MagicCube::UpdateRotation()
    {
        float directionFlag = mRotationState.GetClockwise() == Clockwise::CCW ? 1 : -1;
        switch (mRotationState.GetFace())
        {
        case Face::Right:
            mRotationMatrix = glm::rotate(glm::mat4(1), (float)mCurrentRotationRadius, -glm::vec3(directionFlag, 0, 0));
            break;
        case Face::Up:
            mRotationMatrix = glm::rotate(glm::mat4(1), (float)mCurrentRotationRadius, -glm::vec3(0, directionFlag, 0));
            break;
        case Face::Front:
            mRotationMatrix = glm::rotate(glm::mat4(1), (float)mCurrentRotationRadius, glm::vec3(0, 0, directionFlag));
            break;
        default:
            break;
        }

        mCurrentRotationRadius += mDeltaRadius;

        if (mCurrentRotationRadius > mRotationFinishedRadius)
        {
            mRotationFinished = true;
        }
    }

    void MagicCube::FinishRotation()
    {
        if (mRotationState.IsFinished())
        {
            return;
        }

        mRotationState.mFinished = true;

        for (int i = 0; i < mCountRows; ++i)
        {
            for (int j = 0; j < mCountRows; ++j)
            {
                MagicInsideCube * cube = nullptr;
                if (mRotationState.GetFace() == Face::Right)
                {
                    int index = mCountRows - 1 - mRotationState.GetLineIndex();
                    cube = mInsideCubes[index][i][j];
                }
                else if (mRotationState.GetFace() == Face::Up)
                {
                    int index = mCountRows - 1 - mRotationState.GetLineIndex();
                    cube = mInsideCubes[i][index][j];
                }
                else if (mRotationState.GetFace() == Face::Front)
                {
                    int index = mRotationState.GetLineIndex();
                    cube = mInsideCubes[i][j][index];
                }

                cube->SetRotationMatrix(mRotationState.GetRotationMatrix() * cube->GetRotationMatrix());
            }
        }

        mInsideCubes.Rotate(mRotationState);

        // cleer rotation flags
        for (int i = 0; i < GetCountRows(); ++i)
        {
            for (int j = 0; j < GetCountRows(); ++j)
            {
                for (int k = 0; k < GetCountRows(); ++k)
                {
                    mInsideCubes[i][j][k]->mInRotation = false;
                }
            }
        }
    }

    void MagicCube::OnTimeout()
    {
        if (mRotationFinished)
        {
            FinishRotation();
            mTimer->stop();
        }
        else
        {
            UpdateRotation();
        }

        emit UpdatedSignal();
    }
}