#include "Program.h"

void Program::Create()
{
    if (mCreated == false)
    {
        mCreated = true;
        mID = glCreateProgram();
    }
}

void Program::Destroy()
{
    if (mCreated)
    {
        mCreated = false;
        mLinked = false;
        glDeleteProgram(mID);
    }
}

void Program::AddShader(Shader * shader)
{
    if (mCreated == false)
    {
        Create();
    }

    glAttachShader(mID, shader->GetID());
}

void Program::Link()
{
    if (mLinked == false)
    {
        mLinked = true;
        glLinkProgram(mID);
    }
}

void Program::Bind()
{
    if (mCreated == false)
    {
        Create();
    }

    if (mLinked == false)
    {
        Link();
    }

    glUseProgram(mID);
}

void Program::Unbind()
{
    glUseProgram(0);
}

GLuint Program::GetAttributeID(const char * name)
{
    return glGetAttribLocation(mID, name);
}

GLuint Program::GetUniformID(const char * name)
{
    return glGetUniformLocation(mID, name);
}

void Program::SetAttributeBuffer(GLuint iD, GLint size, GLenum type, GLsizei stride)
{
    glEnableVertexAttribArray(iD);
    glVertexAttribPointer(iD, size, type, GL_FALSE, stride, NULL);
}

void Program::SetUniformValue(const char * name, float x, float y, float z)
{
    GLuint iD = GetAttributeID(name);
    glUniform3f(iD, x, y, z);
}

void Program::SetUniformValue(const char * name, const glm::vec3 * value)
{
    GLuint iD = GetAttributeID(name);
 //   glUniform3f(iD, value->x(), value->y(), value->z());
}

void Program::SetUniformValue(const char * name, const glm::mat4 * value)
{
    GLuint iD = GetUniformID(name);
  //  glUniformMatrix4fv(iD, 1, GL_FALSE, value->constData());
}
