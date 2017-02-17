#include "Thing.h"
#include "Transform.h"
#include "ShaderProgram.h"

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
    mShaderProgram->GetCurrentProgram()->Bind(); // use again !!!
    TransformToShaderProgram();
    OnDraw();
}

void Thing::ChangeShaderProgram(ShaderProgram * shaderProgram)
{
    if (mShaderProgram != shaderProgram)
    {
        mShaderProgram = shaderProgram;
        mProgram = shaderProgram->GetCurrentProgram();
        shaderProgram->GetCurrentProgram()->Bind();
        OnChangeShaderProgram(shaderProgram);
    }
}

void Thing::TransformToShaderProgram()
{
    mShaderProgram->GetCurrentProgram()->Bind(); // before use again !!!
    mShaderProgram->SetModelMatrixFromThing(this);
}

void Thing::UpdateCurrentShaderProgram()
{
    OnChangeShaderProgram(mShaderProgram);
}
