#pragma once

#include <gl/glew.h>

class Buffer
{
public:
    Buffer(GLenum type = GL_ARRAY_BUFFER, GLenum usagePattern = GL_STATIC_DRAW) : mType(type), mUsagePattern(usagePattern) {}
    Buffer(const Buffer &) = default;
    ~Buffer() { Destroy(); }
    Buffer & operator = (const Buffer &) = default;

    void Create();
    void SetData(void * data, GLsizei size);
    void Bind();
    void Unbind();
    void Destroy() { mCreated = false; }
    void SetUsagePattern(int usagePattern = 0) {}

private:
    bool mCreated = false;
    GLuint mBuffer;
    GLenum mUsagePattern;
    GLenum mType;
};
