#include "BasicShaderProgram.h"

void BasicShaderProgram::AddThing(Thing * thing)
{
    thing->mNeedNormal = false;
    thing->mNeedTexture = false;
    if (thing->IsCreated() == false)
    {
        thing->Create();
    }

    mThings.push_back(thing);
}

void BasicShaderProgram::OnCreate()
{
    mVertexShader.CompileFromFile("Shaders/BasicVS.glsl");
    mFragmentShader.CompileFromFile("Shaders/BasicPS.glsl");
    mProgram.AddShader(&mVertexShader);
    mProgram.AddShader(&mFragmentShader);
    mProgram.Link();
}
