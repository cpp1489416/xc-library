#include "Shader.h"

#include <fstream>
#include <cassert>
#include <gl/glew.h>

void Shader::Compile(const char * sourceCode)
{
    mSourceCode = sourceCode;
    Compile();
}

void Shader::CompileFromFile(const char * location)
{
    std::ifstream ifs(location);
    if (!ifs) 
    {
        assert(false);
    }

    mSourceCode.clear();
    while (ifs.good())
    {
        std::string tmp;
        std::getline(ifs, tmp);
        mSourceCode.append(tmp + "\n");
    }
    ifs.close();
    Compile();
}

void Shader::Compile()
{
    const char * sourceCode = mSourceCode.c_str();
    mShader = glCreateShader(mShaderType);
    glShaderSource(mShader, 1, &sourceCode, NULL);
    glCompileShader(mShader);

    GLint success = 0;
    glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);
    assert(success == GL_TRUE);
}
