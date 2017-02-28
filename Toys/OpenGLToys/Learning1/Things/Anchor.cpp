#include "Anchor.h"

void Anchor::OnCreate()
{

    GLfloat arr[] =
    {
        0.0f, 0.0f, 0.0f,
        1, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1,
    };

    GLfloat arrColors[]
    {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };

    mVBOPositions.Bind();
    mVBOPositions.SetData(arr, sizeof(arr));
    mVBOColors.Bind();
    mVBOColors.SetData(arrColors, sizeof(arrColors));
}

void Anchor::OnChangeTechnique(Technique * shaderProgram)
{
    mVAO.Destroy();
    mVAO.Bind();
    GLuint mPositionAttribute = shaderProgram->GetPositionAttribute();
    mVBOPositions.Bind();
    glEnableVertexAttribArray(mPositionAttribute);
    glVertexAttribPointer(mPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    GLuint mColorAttribute = shaderProgram->GetColorAttribute();
    mVBOColors.Bind();
    glEnableVertexAttribArray(mColorAttribute);
    glVertexAttribPointer(mColorAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Anchor::OnDraw()
{
    mVAO.Bind();
    glDrawArrays(GL_LINES, 0, 6);
}
