#pragma once

#include "CXCGL.h"

class BasicShaderProgram : public ShaderProgram
{
public:
    virtual void AddThing(Thing * thing) override;
    virtual Program * GetCurrentProgram() override { return &mProgram; }
    virtual GLuint GetPositionAttribute() override final { return GetAttributeLocation("position"); }
    virtual GLuint GetColorAttribute() override final { return GetAttributeLocation("color"); }
    virtual GLuint GetProjectionMatrixUniform() override final { return GetUniformLocation("projection"); }
    virtual GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    virtual GLuint GetModelMatrixUniform() override final { return GetUniformLocation("model"); }

protected:
    virtual void OnCreate() override final;

private:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
};