#include "LightingTechnique.h"

void LightingTechnique::AddThing(Thing * thing)
{
    thing->mNeedNormal = true;
    thing->mNeedTexture = false;
    if (thing->IsCreated() == false)
    {
        thing->Create();
    }

    mThings.push_back(thing);
}

void LightingTechnique::OnCreate()
{
    mVertexShader.CompileFromFile("Shaders/LightingVertexShader.glsl");
    mFragmentShader.CompileFromFile("Shaders/LightingFragmentShader.glsl");
    mProgram.AddShader(&mVertexShader);
    mProgram.AddShader(&mFragmentShader);
}

void LightingTechnique::SetPointLight(PointLight * pointLight)
{
    mPointLight = pointLight;

    UpdatePointLight();
}

void LightingTechnique::UpdatePointLight()
{
    mProgram.Bind();
    GLuint lightPos = GetLightPositionUniform();
    GLuint lightCol = GetLightIntensitiesUniform();
    glm::vec3 &pos = mPointLight->mPosition;
    glm::vec3 &col = mPointLight->mIntensities;
    glUniform3f(lightPos, pos[0], pos[1], pos[2]);
    glUniform3f(lightCol, col[0], col[1], col[2]);
}

