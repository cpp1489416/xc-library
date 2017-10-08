#pragma once

#include <gl/glew.h>
#include "Texture.h"

class FramebufferObject
{
public:
    void Create();
    bool IsCreated() const { return mCreated; }
    void Destroy();
    void Bind();
    void Unbind();

private:
    bool mCreated = false;
    GLuint mID;
};