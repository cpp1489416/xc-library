#pragma once

#include <gl/glew.h>

class Texture
{
public:
    void Create();
    bool IsCreated() const { return mCreated; }
    void Destroy();
    GLuint GetID() { return mID; }
    void Bind();
    void Unbind();
    void SetData(GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels = nullptr);


private:    
    bool mCreated = false;
    GLuint mID;
};