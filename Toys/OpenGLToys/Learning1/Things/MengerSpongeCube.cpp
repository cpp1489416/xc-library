#include "MengerSpongeCube.h"

/*
void MengerSpongeCube::Create(ShaderProgram * shaderProgram, int depth)
{
    mCube.mNeedNormal = mNeedNormal;
    mCube.Create(shaderProgram);
    mDepth = depth;
}

void MengerSpongeCube::Draw()
{
    DrawInsideCube(0.0f, 0.0f, 0.0f, 1.0f, mDepth);
}

void MengerSpongeCube::Destroy()
{

}

void MengerSpongeCube::DrawInsideCube(float x, float y, float z, float size, int depth)
{
    if (depth == 0)
    {
        // transform of each cube is updated
        glm::vec3 pos = glm::vec3(mTransform.mScale[0] * x, mTransform.mScale[1] * y, mTransform.mScale[2] * z);
        pos = QQuaternion::fromEulerAngles(mTransform.mRotation) * pos;
        mCube.mTransform.mPosition = mTransform.mPosition + pos;

        mCube.mTransform.mScale = mTransform.mScale * size;
        mCube.mTransform.mRotation = mTransform.mRotation;
        mCube.Draw();
        return;
    }
    else
    {
        float newSize = size / 3.0f;
        float offset = newSize + newSize / 2.0f;

        // right face, +X
        DrawInsideCube(x + offset, y - offset, z + offset, newSize, depth - 1);
        DrawInsideCube(x + offset, y - offset, z, newSize, depth - 1);
        DrawInsideCube(x + offset, y - offset, z - offset, newSize, depth - 1);
        DrawInsideCube(x + offset, y, z - offset, newSize, depth - 1);
        DrawInsideCube(x + offset, y + offset, z - offset, newSize, depth - 1);
        DrawInsideCube(x + offset, y + offset, z, newSize, depth - 1);
        DrawInsideCube(x + offset, y + offset, z + offset, newSize, depth - 1);
        DrawInsideCube(x + offset, y, z + offset, newSize, depth - 1);

        // left face, -X
        DrawInsideCube(x - offset, y - offset, z + offset, newSize, depth - 1);
        DrawInsideCube(x - offset, y - offset, z, newSize, depth - 1);
        DrawInsideCube(x - offset, y - offset, z - offset, newSize, depth - 1);
        DrawInsideCube(x - offset, y, z - offset, newSize, depth - 1);
        DrawInsideCube(x - offset, y + offset, z - offset, newSize, depth - 1);
        DrawInsideCube(x - offset, y + offset, z, newSize, depth - 1);
        DrawInsideCube(x - offset, y + offset, z + offset, newSize, depth - 1);
        DrawInsideCube(x - offset, y, z + offset, newSize, depth - 1);

        // up face, +Y
        DrawInsideCube(x, y + offset, z + offset, newSize, depth - 1);
        DrawInsideCube(x, y + offset, z - offset, newSize, depth - 1);

        // down face, -Y
        DrawInsideCube(x, y - offset, z - offset, newSize, depth - 1);
        DrawInsideCube(x, y - offset, z + offset, newSize, depth - 1);

        // front face, +Z
        // none 

        // back face, -Z
        // none
    }
}

*/