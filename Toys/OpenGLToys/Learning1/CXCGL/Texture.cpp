#include "Texture.h"

void Texture::Create()
{
    if (!IsCreated())
    {
        mCreated = true;
        glGenTextures(1, &mID);
    }
}

void Texture::Destroy()
{
    if (IsCreated())
    {
        mCreated = false;
        glDeleteTextures(1, &mID);
    }
}

void Texture::Bind()
{
    if (!IsCreated())
    {
        Create();
    }

    glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetData(
    GLint level,
    GLint internalFormat, 
    GLsizei width, 
    GLsizei height,
    GLint border,
    GLenum format, 
    GLenum type,
    const void * pixels)
{
    Bind();
    glTexImage2D(
        GL_TEXTURE_2D, 
        level/*GLint*/,
        internalFormat/*GLint*/, 
        width/*GLsizei*/,
        height/*GLsizei*/, 
        border/*GLint*/,
        format/*GLenum*/,
        type/*GLenum*/, 
        pixels/*const void **/);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}
