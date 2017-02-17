#pragma once

#include "../CXCGL.h"

class ShadowShaderProgram : public ShaderProgram
{
public:
    void AddThing(Thing * thing) override;
    void DrawAllThings() override;
    Program * GetCurrentProgram() override;
    void SetModelMatrixFromThing(Thing * thing) override;
    void UpdateFromCamera(Camera * camera) override;
    GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    GLuint GetColorAttribute() override { return GetAttributeLocation("color"); }
    GLuint GetNormalAttribute() override { return GetAttributeLocation("normal"); }
    GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    GLuint GetModelMatrixUniform() override { return GetUniformLocation("model"); }
    
public:
    GLuint GetLightProjectionMatrixUniform() { return GetUniformLocation("lightProjection"); }
    GLuint GetLightViewMatrixUniform() { return GetUniformLocation("lightView"); }
    GLuint GetLightModelMatrixUniform() { return GetUniformLocation("lightModel"); }
    GLuint GetLightPositionUniform() { return GetUniformLocation("lightPosition"); }
    void UpdateFromLightCamera(Camera * camera);
    GLuint GetShadowTextureID() { return mShadowTexture.GetID(); }
    void UpdateShadowTexture();
    void ChangeSize(int width, int height);

protected:
    void OnCreate() override;

public:
    int mWidth = 1024;
    int mHeight = 1024;
    float mLargerFactor = 1;

public:
    std::vector<Thing *> mThings;
    FramebufferObject mFBO;
    Texture mShadowTexture;

private:
    bool mInFirstStep = true;
    Program mFirstProgram;
    Shader mFirstVS = Shader(GL_VERTEX_SHADER);
    Shader mFirstPS = Shader(GL_FRAGMENT_SHADER);
    Program mSecondProgram;
    Shader mSecondVS = Shader(GL_VERTEX_SHADER);
    Shader mSecondPS = Shader(GL_FRAGMENT_SHADER);
};
