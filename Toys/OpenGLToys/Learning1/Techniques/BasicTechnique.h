#pragma once

#include "CXCGL.h"

class BasicTechnique : public Technique
{
public:
    void AddThing(Thing * thing) override;
    Program * GetCurrentProgram() override { return &mProgram; }
    GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
    GLuint GetColorAttribute() override  { return GetAttributeLocation("color"); }
    GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
    GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
    GLuint GetModelMatrixUniform() override final { return GetUniformLocation("model"); }

protected:
    virtual void OnCreate() override;

private:
    Program mProgram;
    Shader mVertexShader = Shader(GL_VERTEX_SHADER);
    Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
};