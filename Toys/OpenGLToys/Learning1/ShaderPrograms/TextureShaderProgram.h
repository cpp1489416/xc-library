#pragma once

#include "../CXCGL.h"
#include "../FileLoaders/ImageFileLoader.h"

class TextureShaderProgram : public ShaderProgram
{
public:
    void AddThing(Thing * thing) override;
    Program * GetCurrentProgram() override { return &mProgram; }
    GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    GLuint GetTextureCoordAttribute() override { return GetAttributeLocation("textureCoord"); }
    GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    GLuint GetModelMatrixUniform() override { return GetUniformLocation("model"); }
    GLuint GetTexture2DUniform() override { return GetUniformLocation("picture"); }
    GLuint GetTextureID() override { return mTextureID; }

public:
    void SetPicturePath(const char * path);
    void SetTextureID(GLuint ID) { mTextureID = ID; }

public:
    GLuint mTextureID;

protected:
    void OnCreate() override;

private:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
    ImageFileLoader mFileLoader;
};