#include "Buffer.h"

void Buffer::Create()
{
    if (!mCreated)
    {
        glGenBuffers(1, &mBuffer);
        mCreated = true;
    }
}

void Buffer::SetData(void * data, GLsizei size)
{
    if (!mCreated) 
    {
        Create();
    }

    Bind();
    glBufferData(mType, size, data, mUsagePattern);
}

void Buffer::Bind()
{
    if (!mCreated) 
    {
        Create();
    }

    glBindBuffer(mType, mBuffer);
}

void Buffer::Unbind()
{
    glBindBuffer(mType, 0);
}