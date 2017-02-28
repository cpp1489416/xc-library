#include "Thing.h"
#include "Transform.h"
#include "Technique.h"

void Thing::Create()
{
    if (mCreated == false)
    {
        mCreated = true;
        OnCreate();
    }
}

void Thing::Destroy()
{
}

void Thing::Draw()
{
    mTechnique->GetCurrentProgram()->Bind(); // use again !!!
    TransformToTechnique();
    OnDraw();
}

void Thing::ChangeTechnique(Technique * shaderProgram)
{
    if (mTechnique != shaderProgram)
    {
        mTechnique = shaderProgram;
        mProgram = shaderProgram->GetCurrentProgram();
        shaderProgram->GetCurrentProgram()->Bind();
        OnChangeTechnique(shaderProgram);
    }
}

void Thing::TransformToTechnique()
{
    mTechnique->GetCurrentProgram()->Bind(); // before use again !!!
    mTechnique->SetModelMatrixFromThing(this);
}

void Thing::UpdateCurrentTechnique()
{
    OnChangeTechnique(mTechnique);
}
