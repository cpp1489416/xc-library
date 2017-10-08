#include "TriangularPyramid.h"
#include <algorithm>
#include <random>

namespace
{
    GLfloat GetRandom()
    {
        std::random_device rd;
        return (GLfloat)rd() / (rd.max() - rd.min());
    }
}

/*
TriangularPyramid::TriangularPyramid()
{
}

void TriangularPyramid::Create(Technique * shaderProgram)
{
    mTechnique = shaderProgram;
    GLuint posAttrib = shaderProgram->GetPositionAttribute();
    GLuint colAttrib = shaderProgram->GetColorAttribute();
    
    GLfloat vecs[4 * 3] = 
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    GLfloat cols[4 * 3] =
    {
        GetRandom(), GetRandom(), GetRandom(),
        GetRandom(), GetRandom(), GetRandom(),
        GetRandom(), GetRandom(), GetRandom(),
        GetRandom(), GetRandom(), GetRandom(),
    };

    GLushort indices[12] = 
    {
        0, 1, 2,
        0, 1, 3,
        0, 2, 3,
        1, 2, 3,
    };

    mVAO.Bind();
    mVBOPositions.Bind();
    mVBOPositions.SetData(vecs, sizeof(vecs));
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    mVBOColors.Bind();
    mVBOColors.SetData(cols, sizeof(cols));
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    mEBO.Bind();
    mEBO.SetData(indices, sizeof(indices));
}

void TriangularPyramid::Draw()
{
    mVAO.Bind();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, NULL);
    mVAO.Unbind();
}

void TriangularPyramid::Destroy()
{
    

}
*/