#pragma once
#include "../CXCGL.h"

class LightingShaderProgram : public ShaderProgram
{
public:
    virtual void AddThing(Thing * thing) override;
    virtual Program * GetCurrentProgram() override { return &mProgram; }
    virtual GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    virtual GLuint GetColorAttribute() override { return GetAttributeLocation("color"); }
    virtual GLuint GetNormalAttribute() override { return GetAttributeLocation("normal"); }
    virtual GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    virtual GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    virtual GLuint GetModelMatrixUniform() override { return GetUniformLocation("model"); }
    virtual GLuint GetLightPositionUniform() override { return GetUniformLocation("lightPosition"); }
    virtual GLuint GetLightIntensitiesUniform() override { return GetUniformLocation("lightIntensities"); }
    
public:
    void SetPointLight(PointLight * pointLight);
    void UpdatePointLight();

protected:
    virtual void OnCreate() override;
    
public:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
    PointLight * mPointLight;
};