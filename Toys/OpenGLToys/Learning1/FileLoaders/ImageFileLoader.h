#pragma once

#include <gl/glew.h>

class ImageFileLoader
{
public:
    ImageFileLoader();
    ~ImageFileLoader();

public:
    void Create(const char * path);
    void * GetData();
    GLsizei GetWidth();
    GLsizei GetHeight();
    GLenum GetFormat();
    GLenum GetDataType();

private:
    class IMPL;
    IMPL * mIMPL;
};