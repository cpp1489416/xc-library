#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Program.h"
#include <vector>

class Thing;

class Technique
{
public:
    virtual void Create();
    virtual void Destroy();
    virtual void AddThing(Thing * thing);
    virtual void DrawAllThings();
    virtual void ClearAllThings();
    virtual void SetModelMatrixFromThing(Thing * thing);
    virtual void UpdateFromCamera(Camera * camera) { camera->UpdateToTechnique(this); }
    virtual Program * GetCurrentProgram() { return nullptr; } // get current program
    virtual GLuint GetPositionAttribute() { return GetAttributeLocation("position"); }
    virtual GLuint GetColorAttribute() { return GetAttributeLocation("color"); }
    virtual GLuint GetTextureCoordAttribute() { return GetAttributeLocation("textureCoord"); }
    virtual GLuint GetNormalAttribute() { return GetAttributeLocation("normal"); }
    virtual GLuint GetProjectionMatrixUniform() { return GetAttributeLocation("projection"); }
    virtual GLuint GetViewMatrixUniform() { return GetUniformLocation("view"); }
    virtual GLuint GetModelMatrixUniform() { return GetUniformLocation("model"); }
    virtual GLuint GetLightPositionUniform() { return GetUniformLocation("uniform"); }
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
