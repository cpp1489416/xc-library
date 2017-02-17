#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Program.h"
#include <vector>

class Thing;

class ShaderProgram
{
public:
    virtual void Create();
    virtual void Destroy();
    virtual void AddThing(Thing * thing);
    virtual void DrawAllThings();
    virtual void ClearAllThings();
    virtual void SetModelMatrixFromThing(Thing * thing);
    virtual void UpdateFromCamera(Camera * camera) { camera->UpdateToShaderProgram(this); }
    virtual Program * GetCurrentProgram() { return nullptr; } // get current program
    virtual GLuint GetPositionAttribute() { return 0; }
    virtual GLuint GetColorAttribute() { return 0; }
    virtual GLuint GetTextureCoordAttribute() { return 0; }
    virtual GLuint GetNormalAttribute() { return 0; }
    virtual GLuint GetProjectionMatrixUniform() { return 0; }
    virtual GLuint GetViewMatrixUniform() { return 0; }
    virtual GLuint GetModelMatrixUniform() { return 0; }
    virtual GLuint GetLightPositionUniform() { return 0; }
    virtual GLuint GetLightIntensitiesUniform() { return 0; }
    virtual GLuint GetTexture2DUniform() { return 0; }
    virtual GLuint GetTextureID() { return 0; }
    
public:
    GLuint GetAttributeLocation(const char * name) { return GetCurrentProgram()->GetAttributeID(name); }
    GLuint GetUniformLocation(const char * name) { return GetCurrentProgram()->GetUniformID(name); }

protected:
    virtual void OnCreate() {}
   
protected:
    std::vector<Thing *> mThings;

private:
    bool mCreated = false;
};
