#pragma once

#include <glm/glm.hpp>
#include <QVector>
#include <QQuaternion>
#include <glm/glm.hpp>

class Transform
{
public:
    Transform();

public:
    glm::mat4 * GetMatrix();
    
public:
    glm::vec3 mPosition = glm::vec3(0, 0, 0);
    glm::vec3 mRotation = glm::vec3(0, 0, 0);
    glm::vec3 mScale = glm::vec3(1, 1, 1);
    glm::mat4 mMatrix;

private:
    void UpdateMatrix();
};