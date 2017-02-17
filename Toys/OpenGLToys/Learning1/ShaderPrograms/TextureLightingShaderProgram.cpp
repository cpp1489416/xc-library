#include "TextureLightingShaderProgram.h"


void TextureLightingShaderProgram::AddThing(Thing * thing)
{
    thing->mNeedNormal = true;
    thing->mNeedTexture = true;
    if (thing->IsCreated() == false)
    {
        thing->Create();
    }

    mThings.push_back(thing);
}

void TextureLightingShaderProgram::SetPointLight(PointLight * pointLight)
{
    mPointLight = pointLight;

    UpdatePointLight();
}

void TextureLightingShaderProgram::UpdatePointLight()
{
    mProgram.Bind();
    GLuint lightPos = GetLightPositionUniform();
    GLuint lightCol = GetLightIntensitiesUniform();
    glm::vec3 &pos = mPointLight->mPosition;
    glm::vec3 &col = mPointLight->mIntensities;
    glUniform3f(lightPos, pos[0], pos[1], pos[2]);
    glUniform3f(lightCol, col[0], col[1], col[2]);
}

void TextureLightingShaderProgram::SetPicturePath(const char * path)
{
    mProgram.Bind();
    glGenTextures(1, &mTextureID);
    mFileLoader.Create(path);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    glTexImage2D(
        GL_TEXTURE_2D,
        0, // level
        mFileLoader.GetFormat(), // GL_RGBA
        mFileLoader.GetWidth(),
        mFileLoader.GetHeight(),
        0, // border
        mFileLoader.GetFormat(), // GL_RGBA
        mFileLoader.GetDataType(), // GL_UNSIGNED_BYTE
        mFileLoader.GetData());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void TextureLightingShaderProgram::OnCreate()
{
    mVertexShader.CompileFromFile("Shaders/TextureLightingVertexShader.glsl");
    mFragmentShader.CompileFromFile("Shaders/TextureLightingFragmentShader.glsl");
    mProgram.AddShader(&mVertexShader);
    mProgram.AddShader(&mFragmentShader);
}
