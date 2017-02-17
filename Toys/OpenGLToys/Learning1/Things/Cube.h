#pragma once

#include "CXCGL.h"

class Cube : public Thing
{
public:
    virtual void OnCreate() override;
    virtual void OnDraw() override;
    virtual void OnChangeShaderProgram(ShaderProgram * shaderProgram) override;

private:
    VertexArrayObject mVAO;
    Buffer mVBOPositions = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOColors = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBONormals = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
};