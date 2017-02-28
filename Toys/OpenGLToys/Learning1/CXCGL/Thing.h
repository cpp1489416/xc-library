#pragma once

#include "Transform.h"
#include "Program.h"
#include "Buffer.h"

#include <vector>

class Technique;

enum class VertexType
{
    Position, Color, TextureCoord, Normal,
};

class Thing
{
public:
    void Create();
    virtual void Destroy();
    virtual void ChangeTechnique(Technique * shaderProgram);
    virtual void Draw();
    virtual void TransformToTechnique();
    virtual bool IsCreated() const { return mCreated; }
    virtual void UpdateCurrentTechnique();
    virtual void OnCreate() {}
    virtual void OnChangeTechnique(Technique * shaderProgram) {}
    virtual void OnDraw() {}
    virtual void OnDestroy() {}

public:
    Transform mTransform;
    bool mNeedNormal = false;
    bool mNeedTexture = false;


protected:
    Buffer * GetArrayBuffer(VertexType vertexType) { return nullptr; }
    Buffer * GetElementBuffer() { return nullptr; }
    Buffer * GetRubbishBuffer() { return nullptr; }
    void SetVertexBufferData(VertexType vertexType, void * buffer, size_t size) {}
    
protected:
    bool mCreated = false;
    Technique * mTechnique;
    Program * mProgram;

private:
    Buffer mPositionBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mColorBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mTextureCoordBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mNormalBuffer = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
};