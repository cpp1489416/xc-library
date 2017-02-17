#pragma once

#include "ShaderProgram.h"
#include <glm/glm.hpp>

class PointLight
{
public:
    void Create(ShaderProgram * shaderProgram);
    void Update();

public:
    glm::vec3 mIntensities = glm::vec3(1, 1, 1);
    glm::vec3 mPosition = glm::vec3(0, 0, 0);
    ShaderProgram * mShaderProgram;
};