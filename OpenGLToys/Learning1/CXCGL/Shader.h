#pragma once 

#include <gl/glew.h>
#include <string>

class Shader
{
public:


public:
    Shader(GLenum shaderType = GL_VERTEX_SHADER) : mShaderType(shaderType) {}

    void Compile(const char * sourceCode);
    void CompileFromFile(const char * location);
    void Compile();
    GLuint GetID() const { return mShader; }

private:
    GLenum mShaderType;
    std::string mSourceCode;
    GLuint mShader;
    
   
};