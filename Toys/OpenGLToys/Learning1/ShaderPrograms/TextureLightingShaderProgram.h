#pragma once

#include "../CXCGL.h"
#include "../FileLoaders/ImageFileLoader.h"

class TextureLightingShaderProgram : public ShaderProgram
{
public:
    virtual void AddThing(Thing * thing) override;
    virtual Program * GetCurrentProgram() override { return &mProgram; }
    virtual GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    virtual GLuint GetTextureCoordAttribute() override { return GetAttributeLocation("textureCoord"); }
    virtual GLuint GetNormalAttribute() override { return GetAttributeLocation("normal"); }
    virtual GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    virtual GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    virtual GLuint GetModelMatrixUniform() override { return GetUniformLocation("model"); }
    virtual GLuint GetTexture2DUniform() override { return GetUniformLocation("picture"); }
    virtual GLuint GetTextureID() override { return mTextureID; }
    virtual GLuint GetLightPositionUniform() override { return GetUniformLocation("lightPosition"); }
    virtual GLuint GetLightIntensitiesUniform() override { return GetUniformLocation("lightIntensities"); }
    void SetPointLight(PointLight * pointLight);
    void UpdatePointLight();
    void Update() {}

public:
    void SetPicturePath(const char * path);
    void SetTextureID(GLuint ID) { mTextureID = ID; }

public:
    PointLight * mPointLight;
    GLuint mTextureID;

protected:
    virtual void OnCreate() override;

private:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
    ImageFileLoader mFileLoader;
};