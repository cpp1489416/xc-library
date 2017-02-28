#include "MagicCube.h"
#include "MagicCubeRotationState.h"
#include "../CXCGL/Technique.h"

namespace MagicCube
{
    MagicCube::MagicCube(int countRows) // count if rows is always 4
    {
    }

    MagicInsideCube * MagicCube::GetInsideCube(int x, int y, int z) const
    {
        return mInsideCubes[x][y][z];
    }

    void MagicCube::SetRotationState(const RotationState & rotationState)
    {
        mRotationState = rotationState;
    }

    void MagicCube::Update()
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
                    int index = 3 - mRotationState.GetLineIndex();
                    cube = mInsideCubes[index][i][j];
                }
                else if (mRotationState.GetFace() == Face::Up)
                {
                    int index = 3 - mRotationState.GetLineIndex();
                    cube = mInsideCubes[i][index][j];
                }
                else if (mRotationState.GetFace() == Face::Front)
                {
                    int index = 3 - mRotationState.GetLineIndex();
                    cube = mInsideCubes[i][j][index];
                }

                cube->SetRotationMatrix(cube->GetRotationMatrix() * mRotationState.GetRotationMatrix());
            }
        }
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
                    float xDiff = (i - (mCountRows / 2.0f - 0.5f)) * 2.0f;
                    float yDiff = (j - (mCountRows / 2.0f - 0.5f)) * 2.0f;
                    float zDiff = (k - (mCountRows / 2.0f - 0.5f)) * 2.0f;
                    glm::mat4 translateMatrix = glm::translate(glm::mat4(1), glm::vec3(xDiff, yDiff, zDiff));
                    glm::mat4 rotationMatrix = cube->GetRotationMatrix();
                    glm::mat4 modelMatrix = translateMatrix * rotationMatrix * selfModelMatrix;
                    glUniformMatrix4fv(mTechnique->GetUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
                    cube->OnDraw();
                }
            }
        }
    }

    void MagicCube::InitializeInsideCubes()
    {
        for (int i = 0; i < mCountRows * mCountRows * mCountRows; ++i)
        {
            mInsideCubes[i / mCountRows / mCountRows][(i / mCountRows) % mCountRows][i % mCountRows] = new MagicInsideCube();
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
                mInsideCubes[i][j][mCountRows]->SetFaceColor(Direction::Back, Color::Green);

                // front face is blue
                mInsideCubes[i][j][0]->SetFaceColor(Direction::Front, Color::Blue);
            }
        }

        for (int i = 0; i < mCountRows * mCountRows * mCountRows; ++i)
        {
            mInsideCubes[i / mCountRows / mCountRows][(i / mCountRows) % mCountRows][i % mCountRows]->Create();
        }
    }

    void MagicCube::DestoryInsideCubes()
    {
        for (int i = 0; i < mCountRows * mCountRows * mCountRows; ++i)
        {
            delete mInsideCubes[i / mCountRows / mCountRows][(i / mCountRows) % mCountRows][i % mCountRows];
        }
    }
}