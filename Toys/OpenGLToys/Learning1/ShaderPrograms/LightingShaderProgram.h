#pragma once
#include "../CXCGL.h"

class LightingShaderProgram : public ShaderProgram
{
public:
    void AddThing(Thing * thing) override;
    Program * GetCurrentProgram() override { return &mProgram; }
    GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    GLuint GetColorAttribute() override { return GetAttributeLocation("color"); }
    GLuint GetNormalAttribute() override { return GetAttributeLocation("normal"); }
    GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    GLuint GetModelMatrixUniform() override { return GetUniformLocation("model"); }
    GLuint GetLightPositionUniform() override { return GetUniformLocation("lightPosition"); }
    GLuint GetLightIntensitiesUniform() override { return GetUniformLocation("lightIntensities"); }

public:
    void SetPointLight(PointLight * pointLight);
    void UpdatePointLight();

protected:
    void OnCreate() override;

public:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
    PointLight * mPointLight;
};