#pragma once

#include "CXCGL.h"

class Anchor : public Thing
{
public:
    virtual void OnCreate() override;
    virtual void OnDraw() override;
    virtual void OnChangeShaderProgram(ShaderProgram * shaderProgram) override;

public:
    VertexArrayObject mVAO;
    Buffer mVBOPositions = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOColors = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
};