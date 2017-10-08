#pragma once

#include <gl/glew.h> // i dont want to include it but i cannot
#include <cstdlib>

class DDSFileLoader
{
public:
    static GLuint Read(const char * path);
};