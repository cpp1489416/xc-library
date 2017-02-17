#include "Transform.h"
#include <glm/ext.hpp>

namespace
{
    float PI = 3.14;
    float angleToRad = PI / 180.f;
}

Transform::Transform()
{
}

glm::mat4 * Transform::GetMatrix()
{
    UpdateMatrix();
    return &mMatrix;
}

void Transform::Ratate(float angle, glm::vec3 & axis)
{
}

void Transform::UpdateMatrix()
{
    glm::mat4 ans = glm::mat4(1.0f);

    ans = glm::translate(ans, mPosition);
    ans = glm::rotate(ans, mRotation[0] * angleToRad, glm::vec3(1.0f, 0, 0));
    ans = glm::rotate(ans, mRotation[1] * angleToRad, glm::vec3(0, 1, 0));
    ans = glm::rotate(ans, mRotation[2] * angleToRad, glm::vec3(0, 0, 1));
    ans = glm::scale(ans, mScale);
    mMatrix = ans;
}
