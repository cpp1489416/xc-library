#pragma once

#include <gl/glew.h>

class VertexArrayObject
{
public:
    void Create();
    void Bind();
    void Unbind();
    void Destroy(); // destroy must be called expecitally

public:
    GLuint mVAO;

private:
    bool mCreated = false;
};