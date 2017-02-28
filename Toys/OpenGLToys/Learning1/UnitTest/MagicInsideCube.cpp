#include "MagicInsideCube.h"

MagicInsideCube::MagicInsideCube()
{
    for (int i = 0; i < 6; ++i)
    {
        // all the faces is automatically black
        mFaceColors[i] = Color::Black;
    }
}

void MagicInsideCube::SetFaceColor(Face face, Color color)
{
    int faceID = static_cast<int>(face);
    mFaceColors[faceID] = color;
}

void MagicInsideCube::OnCreate()
{
    float positions[] =
    {
        // right face
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

        // left face
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        // up face
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,

        // down face
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,

        // back face
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,

        // front face
        -1.0f, -1.0f, -1.0f, 
        1.0f, -1.0f, -1.0f,  
        1.0f, 1.0f, -1.0f,  
        1.0f, 1.0f, -1.0f,  
        -1.0f, 1.0f, -1.0f, 
        -1.0f, -1.0f, -1.0f,
    };

    float colors[6 * 6 * 3];
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            size_t location = i * 6 * 6 * 3 + j * 3;
            SetColor(colors + location, mFaceColors[i]);
        }
    }

    mVertexArrayObject.Create();
    mVertexArrayObject.Bind();
    
    mPositionArrayBuffer.Create();
    mPositionArrayBuffer.SetData((void *)positions, sizeof(positions));
    glEnableVertexAttribArray(Program::GetPositionAttributeID());
    glVertexAttribPointer(Program::GetPositionAttributeID(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    mColorArrayBuffer.Create();
    mColorArrayBuffer.SetData((void *)colors, sizeof(colors));
    glEnableVertexAttribArray(Program::GetColorAttributeID());
    glVertexAttribPointer(Program::GetColorAttributeID(), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    mVertexArrayObject.Unbind();
}

void MagicInsideCube::OnDraw()
{
    mVertexArrayObject.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MagicInsideCube::SetColor(float * vertex, Color color)
{
    switch (color)
    {
    case MagicInsideCube::Color::White:
        vertex[0] = 1;
        vertex[1] = 1;
        vertex[2] = 1;
        break;
    case MagicInsideCube::Color::Green:
        vertex[0] = 0;
        vertex[1] = 1;
        vertex[2] = 0;
        break;
    case MagicInsideCube::Color::Yellow:
        vertex[0] = 1;
        vertex[1] = 1;
        vertex[2] = 0;
        break;
    case MagicInsideCube::Color::Blue:
        vertex[0] = 0;
        vertex[1] = 0;
        vertex[2] = 1;
        break;
    case MagicInsideCube::Color::Red:
        vertex[0] = 1;
        vertex[1] = 0;
        vertex[2] = 0;
        break;
    case MagicInsideCube::Color::Orange:
        vertex[0] = 1;
        vertex[1] = 0.5f;
        vertex[2] = 0;
        break;
    case MagicInsideCube::Color::Black:
        vertex[0] = 0;
        vertex[1] = 0;
        vertex[2] = 0;
        break;
    default:
        break;
    }
}
