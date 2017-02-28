#include "Technique.h"
#include "Thing.h"

void Technique::Create()
{
    if (!mCreated)
    {
        mCreated = true;
        OnCreate();
    }
}

void Technique::AddThing(Thing * thing)
{
    if (thing->IsCreated() == false)
    {
        thing->Create();
    }

    thing->ChangeTechnique(this);
    mThings.push_back(thing);
}

void Technique::DrawAllThings()
{
    for (auto i : mThings)
    {
        i->ChangeTechnique(this);
        i->Draw();
    }
}

void Technique::ClearAllThings()
{
    mThings.clear();
}

void Technique::SetModelMatrixFromThing(Thing * thing)
{
    GetCurrentProgram()->Bind();
    GLuint modelMatrixID = GetModelMatrixUniform();
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &(*thing->mTransform.GetMatrix())[0][0]);
}

void Technique::Destroy()
{
}
