#pragma once

#include "Transform.h"
#include "Program.h"

class ShaderProgram;

class Thing
{    
public:
    virtual void Create();
    virtual void Destroy();
    virtual void ChangeShaderProgram(ShaderProgram * shaderProgram);
    virtual void Draw();
    virtual void TransformToShaderProgram();
    virtual bool IsCreated() const { return mCreated; }
    virtual void UpdateCurrentShaderProgram();

protected:
    virtual void OnCreate() {}
    virtual void OnChangeShaderProgram(ShaderProgram * shaderProgram) {}
    virtual void OnDraw() {}
    virtual void OnDestroy() {}

public:
    Transform mTransform;
    bool mNeedNormal = false;
    bool mNeedTexture = false;

protected:
    bool mCreated = false;
    ShaderProgram * mShaderProgram;
    Program * mProgram;
};