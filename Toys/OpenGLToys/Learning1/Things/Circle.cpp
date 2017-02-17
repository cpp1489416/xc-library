#include "Circle.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace
{
    static GLfloat PI = 3.14159f;
}

/*

void Circle::Create(ShaderProgram * shaderProgram)
{
    srand(time(NULL));

    mShaderProgram = shaderProgram;
    GLuint mPositionAttribute = shaderProgram->GetPositionAttribute();
    GLuint mColorAttribute = shaderProgram->GetColorAttribute();
    
    GLfloat *circle = new GLfloat[3 * mCircleSeeds];
    for (int i = 0; i < mCircleSeeds; ++i)
    {
        circle[3 * i] = std::cos(2 * PI / mCircleSeeds * i);
        circle[3 * i + 1] = std::sin(2 * PI / mCircleSeeds * i);
        circle[3 * i + 2] = 0.0f;
    }
    
    GLfloat *circleColors = new GLfloat[3 * mCircleSeeds];
    for (int i = 0; i < mCircleSeeds; ++i)
    {
        circleColors[3 * i] = rand() % 2;
        circleColors[3 * i + 1] = rand() % 2;
        circleColors[3 * i + 2] = rand() % 2;
    }

    mVAO.Generate();
    mVBOPositions.Generate();
    mVBOColors.Generate();

    mVAO.Bind();
    mVBOPositions.Bind();
    mVBOPositions.SetData(circle, 3 * mCircleSeeds * sizeof(GLfloat));
    glEnableVertexAttribArray(mPositionAttribute);
    glVertexAttribPointer(mPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    mVBOColors.Bind();
    mVBOColors.SetData(circleColors, 3 * mCircleSeeds * sizeof(GLfloat));
    glEnableVertexAttribArray(mColorAttribute);
    glVertexAttribPointer(mColorAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    mVBOColors.Unbind();
    mVAO.Unbind();

    delete circle;
    delete circleColors;
}

void Circle::Destroy()
{

}

void Circle::Draw()
{
    mVAO.Bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, mCircleSeeds);
}

*/