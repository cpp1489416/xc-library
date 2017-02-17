#include "FramebufferObject.h"

void FramebufferObject::Create()
{
    if (mCreated == false)
    {
        mCreated = true;
        glGenFramebuffers(1, &mID);
    }
}

void FramebufferObject::Destroy()
{
    if (mCreated)
    {
        mCreated = false;
        glDeleteFramebuffers(1, &mID);
    }
}

void FramebufferObject::Bind()
{
    if (mCreated == false)
    {
        Create();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, mID);
}

void FramebufferObject::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

