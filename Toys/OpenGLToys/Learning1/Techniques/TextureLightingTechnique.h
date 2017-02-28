#pragma once

#include "../CXCGL.h"
#include "../FileLoaders/ImageFileLoader.h"

class TextureLightingTechnique : public Technique
{
public:
    void AddThing(Thing * thing) override;
    Program * GetCurrentProgram() override { return &mProgram; }
    GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    GLuint GetTextureCoordAttribute() override { return GetAttributeLocation("textureCoord"); }
    GLuint GetNormalAttribute() override { return GetAttributeLocation("normal"); }
    GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    GLuint GetModelMatrixUniform() override { return GetUniformLocation("model"); }
    GLuint GetTexture2DUniform() override { return GetUniformLocation("picture"); }
    GLuint GetTextureID() override { return mTextureID; }
    GLuint GetLightPositionUniform() override { return GetUniformLocation("lightPosition"); }
    GLuint GetLightIntensitiesUniform() override { return GetUniformLocation("lightIntensities"); }
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
    void OnCreate() override;

private:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
    ImageFileLoader mFileLoader;
};