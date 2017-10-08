#pragma once

#include "../CXCGL.h"

class Quad : public Thing
{
public:
    virtual void OnCreate() override;
    virtual void OnChangeTechnique(Technique * shaderProgram) override;
    virtual void OnDraw() override;

private:
    VertexArrayObject mVAO;
    Buffer mVBOPositions = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOColors = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOnormals = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOTextureCoords = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
};