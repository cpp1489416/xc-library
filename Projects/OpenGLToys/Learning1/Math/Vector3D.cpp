#include "Vector3D.h"
#include <glm/mat4x4.hpp>

Vector3D::Vector3D(float x, float y, float z)
{
    At(0) = x;
    At(1) = y;
    At(2) = z;
}

Vector3D::Self Vector3D::operator-(Self & rhs)
{
    Self ans;
    ans[0] = At(0);
    return ans;
}

float Vector3D::GetLength()
{
    return At(0) * At(0) + At(1) * At(1) + At(2) * At(2);
}
