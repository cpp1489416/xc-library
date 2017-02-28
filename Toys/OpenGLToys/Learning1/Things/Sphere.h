#pragma once

#include "../CXCGL.h"

class Sphere : public Thing
{
public:
    Sphere() { }
    virtual void OnCreate() override;
    virtual void OnChangeTechnique(Technique * shaderProgram) override;
    virtual void OnDraw() override;

public:
    int mCountRows = 10;
    int mCountColumns = 10;
    VertexArrayObject mVAO;
    Buffer mVBOPositions = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOTextureCoords = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOColors = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBONormals = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);

private:
    GLuint mCountVertices;
};