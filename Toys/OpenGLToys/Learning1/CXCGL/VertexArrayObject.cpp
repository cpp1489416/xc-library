#include "VertexArrayObject.h"

void VertexArrayObject::Create()
{
    if (!mCreated)
    {
        glGenVertexArrays(1, &mVAO);
        mCreated = true;
    }
}

void VertexArrayObject::Bind()
{
    if (!mCreated)
    {
        Create();
        mCreated = true;
    }

    glBindVertexArray(mVAO);
}

void VertexArrayObject::Unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::Destroy()
{
    if (mCreated)
    {
        mCreated = false;
        glDeleteVertexArrays(1, &mVAO);
    }
}
