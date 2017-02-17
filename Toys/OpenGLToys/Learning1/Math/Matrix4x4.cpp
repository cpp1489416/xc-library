#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
    
}

float & Matrix4x4::operator () (int row, int column)
{
    return mData[4 * row + column];
}

Matrix4x4 Matrix4x4::GetIdentity()
{
    Matrix4x4 ans;
    ans.SetToIdentity();
    return ans;
}

void Matrix4x4::SetToIdentity()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; i < 4; j++)
        {
            (*this)(i, j) = 0.0f;
        }

        (*this)(i, i) = 1.0f;
    }
}
