#pragma once 

#include <gl/glew.h>
#include "Shader.h"
#include <glm/glm.hpp>

class Program
{
public:
    static int GetPositionAttributeID() { return 0; }
    static int GetColorAttributeID() { return 1; }
    static int GetTextureCoordAttributeID() { return 2; }
    static int GetNormalAttributeID() { return 3; }
    static int GetInstancedModelMatrixAttributeID() { return 10; }

public:
    void Create();
    void Destroy();
    void AddShader(Shader * shader);
    void Link();
    void Bind();
    void Unbind();
    GLuint GetAttributeID(const char * name);
    GLuint GetUniformID(const char * name);
    void SetAttributeBuffer(GLuint iD, GLint size, GLenum type, GLsizei stride);
    void SetUniformValue(const char * name, float x, float y, float z);
    void SetUniformValue(const char * name, const glm::vec3 * value);
    void SetUniformValue(const char * name, const glm::mat4 * value);

private:
    bool mCreated = false;
    bool mLinked = false;
    GLuint mID;
};