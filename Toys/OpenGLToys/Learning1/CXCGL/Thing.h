#pragma once

#include "Transform.h"
#include "Program.h"
#include "Buffer.h"

#include <vector>

class ShaderProgram;

enum class VertexType
{
    Position, Color, TextureCoord, Normal,
};

class Thing
{
public:
    void Create();
    virtual void Destroy();
    virtual void ChangeShaderProgram(ShaderProgram * shaderProgram);
    virtual void Draw();
    virtual void TransformToShaderProgram();
    virtual bool IsCreated() const { return mCreated; }
    virtual void UpdateCurrentShaderProgram();

public:
    Transform mTransform;
    bool mNeedNormal = false;
    bool mNeedTexture = false;

protected:
    virtual void OnCreate() {}
    virtual void OnChangeShaderProgram(ShaderProgram * shaderProgram) {}
    virtual void OnDraw() {}
    virtual void OnDestroy() {}

protected:
    Buffer * GetArrayBuffer(VertexType vertexType) { return nullptr; }
    Buffer * GetElementBuffer() { return nullptr; }
    Buffer * GetRubbishBuffer() { return nullptr; }
    void SetVertexBufferData(VertexType vertexType, void * buffer, size_t size) {}
    
protected:
    bool mCreated = false;
    ShaderProgram * mShaderProgram;
    Program * mProgram;

private:
    Buffer mPositionBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mColorBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mTextureCoordBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mNormalBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
};