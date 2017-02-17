#include "TextureShaderProgram.h"


void TextureShaderProgram::AddThing(Thing * thing)
{
    thing->mNeedTexture = true;
    thing->mNeedNormal = false;
    if (thing->IsCreated() == false)
    {
        thing->Create();
    }

    mThings.push_back(thing);
}

void TextureShaderProgram::SetPicturePath(const char * path)
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

void TextureShaderProgram::OnCreate()
{
    mVertexShader.CompileFromFile("Shaders/TextureVertexShader.glsl");
    mFragmentShader.CompileFromFile("Shaders/TextureFragmentShader.glsl");
    mProgram.AddShader(&mVertexShader);
    mProgram.AddShader(&mFragmentShader);
}
