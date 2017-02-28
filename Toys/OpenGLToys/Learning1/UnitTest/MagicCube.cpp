#include "MagicCube.h"

MagicCube::MagicCube(int countRows)
{
}

MagicInsideCube * MagicCube::GetInsideCube(int x, int y, int z) const
{
    return mInsideCubes[x][y][z];
}

void MagicCube::RequsetRotationState(const RotationState & rotationState)
{
}

void MagicCube::OnCreate()
{
    InitializeInsideCubes();
}

void MagicCube::OnDraw()
{
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
            mInsideCubes[mCountRows - 1][i][j]->SetFaceColor(MagicInsideCube::Face::Right, MagicInsideCube::Color::Red);

            // left face is orange
            mInsideCubes[0][i][j]->SetFaceColor(MagicInsideCube::Face::Left, MagicInsideCube::Color::Orange);

            // up face is yellow
            mInsideCubes[i][mCountRows - 1][j]->SetFaceColor(MagicInsideCube::Face::Up, MagicInsideCube::Color::Yellow);

            // down face is white
            mInsideCubes[i][0][j]->SetFaceColor(MagicInsideCube::Face::Down, MagicInsideCube::Color::White);

            // back face is green 
            mInsideCubes[i][j][mCountRows]->SetFaceColor(MagicInsideCube::Face::Back, MagicInsideCube::Color::Green);

            // front face is blue
            mInsideCubes[i][j][0]->SetFaceColor(MagicInsideCube::Face::Front, MagicInsideCube::Color::Blue);
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
