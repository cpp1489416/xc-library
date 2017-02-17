#include "ShaderProgram.h"
#include "Thing.h"

void ShaderProgram::Create()
{
    if (!mCreated)
    {
        mCreated = true;
        OnCreate();
    }
}

void ShaderProgram::AddThing(Thing * thing)
{
    if (thing->IsCreated() == false)
    {
        thing->Create();
    }

    thing->ChangeShaderProgram(this);
    mThings.push_back(thing);
}

void ShaderProgram::DrawAllThings()
{
    for (auto i : mThings)
    {
        i->ChangeShaderProgram(this);
        i->Draw();
    }
}

void ShaderProgram::ClearAllThings()
{
    mThings.clear();
}

void ShaderProgram::SetModelMatrixFromThing(Thing * thing)
{
    GetCurrentProgram()->Bind();
    GLuint modelMatrixID = GetModelMatrixUniform();
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &(*thing->mTransform.GetMatrix())[0][0]);
}

void ShaderProgram::Destroy()
{
}
