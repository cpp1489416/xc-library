#include "Sphere.h"
#include <vector>
#include <cmath>

namespace
{
    const GLfloat PI = 3.14159f;

    void QuickPush(std::vector<GLfloat> &vec, GLfloat x, GLfloat y, GLfloat z)
    {
        vec.push_back(x);
        vec.push_back(y);
        vec.push_back(z);
    }

    void QuickPush(std::vector<GLfloat> &vec, GLfloat u, GLfloat v)
    {
        vec.push_back(u);
        vec.push_back(v);
    }

    glm::vec3 GetCentreVector(glm::vec3 a, glm::vec3 b, glm::vec3 c)
    {
        return (a + b + c) * 0.3333333f;
    }

    glm::vec3 GetCentreVector(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
    {
        glm::vec3 a(x1, y1, z1);
        glm::vec3 b(x2, y2, z2);
        glm::vec3 c(x3, y3, z3);

        return GetCentreVector(a, b, c);
    }
}

void Sphere::OnCreate()
{
    mCountVertices = 0;

    std::vector<GLfloat> points;
    std::vector<GLfloat> textureCoords;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> normals;

    for (int i = 0; i < mCountRows - 1; ++i)
    {
        GLfloat y = 1.0f - 2.0f / (mCountRows - 1) * i;
        GLfloat yR = y;
        GLfloat yD = 1.0f - 2.0f / (mCountRows - 1) * (i + 1);
        GLfloat yRD = yD;

        GLfloat r = sqrt(1.0f - fabs(y) * fabs(y));
        GLfloat rD = sqrt(1.0f - fabs(yD) * fabs(yD));

        GLfloat v = 1.0f - 1.0f / (mCountRows - 1) * i;
        GLfloat vR = v;
        GLfloat vD = 1.0f - 1.0f / (mCountRows - 1) * (i + 1);
        GLfloat vRD = vD;

        for (int j = 0; j < mCountColumns; ++j)
        {
            GLfloat x = r * std::cos(2 * PI / mCountColumns * j);
            GLfloat xR = r * std::cos(2 * PI / mCountColumns * (j + 1));
            GLfloat xD = rD * std::cos(2 * PI / mCountColumns * j);
            GLfloat xRD = rD * std::cos(2 * PI / mCountColumns * (j + 1));

            GLfloat z = r * std::sin(2 * PI / mCountColumns * j);
            GLfloat zR = r * std::sin(2 * PI / mCountColumns * (j + 1));
            GLfloat zD = rD * std::sin(2 * PI / mCountColumns * j);
            GLfloat zRD = rD * std::sin(2 * PI / mCountColumns * (j + 1));

            GLfloat u = 1.0f / mCountColumns * j;
            GLfloat uR = 1.0f / mCountColumns * (j + 1);
            GLfloat uD = u;
            GLfloat uRD = uR;

            // left down triangle
            QuickPush(points, x, y, z);
            QuickPush(textureCoords, u, v);
            QuickPush(points, xD, yD, zD);
            QuickPush(textureCoords, uD, vD);
            QuickPush(points, xR, yR, zR);
            QuickPush(textureCoords, uR, vR);

            glm::vec3 normal = GetCentreVector(x, y, z, xD, yD, zD, xR, yR, zR);
            QuickPush(normals, normal[0], normal[1], normal[2]);
            QuickPush(normals, normal[0], normal[1], normal[2]);
            QuickPush(normals, normal[0], normal[1], normal[2]);

            // right up triangle
            QuickPush(points, xD, yD, zD);
            QuickPush(textureCoords, uD, vD);
            QuickPush(points, xRD, yRD, zRD);
            QuickPush(textureCoords, uRD, vRD);
            QuickPush(points, xR, yR, zR);
            QuickPush(textureCoords, uR, vR);

            normal = GetCentreVector(xD, yD, zD, xRD, yRD, zRD, xR, yR, zR);
            QuickPush(normals, normal[0], normal[1], normal[2]);
            QuickPush(normals, normal[0], normal[1], normal[2]);
            QuickPush(normals, normal[0], normal[1], normal[2]);

            mCountVertices += 6;
        }
    }

    for (int i = 0; i < mCountVertices; ++i)
    {
        QuickPush(colors, 1, 1, 1);
    }

    mVBOPositions.Bind();
    mVBOPositions.SetData(&points[0], points.size() * sizeof(GL_FLOAT));

    mVBOTextureCoords.Bind();
    mVBOTextureCoords.SetData(&textureCoords[0], textureCoords.size() * sizeof(GL_FLOAT));

    mVBOColors.Bind();
    mVBOColors.SetData(&colors[0], colors.size() * sizeof(GL_FLOAT));

    mVBONormals.Bind();
    mVBONormals.SetData(&normals[0], normals.size() * sizeof(GL_FLOAT));
}

void Sphere::OnDraw()
{
    mVAO.Bind();
    if (mNeedTexture)
    {
        glBindTexture(GL_TEXTURE_2D, mShaderProgram->GetTextureID());
    }
    
    glDrawArrays(GL_TRIANGLES, 0, mCountVertices);
}

void Sphere::OnChangeShaderProgram(ShaderProgram * shaderProgram)
{
    mVAO.Bind();

    mVBOPositions.Bind();
    GLuint positionID = shaderProgram->GetPositionAttribute();
    glEnableVertexAttribArray(positionID);
    glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    if (mNeedTexture)
    {
        mVBOTextureCoords.Bind();
        GLuint textureCoordID = shaderProgram->GetTextureCoordAttribute();
        glEnableVertexAttribArray(textureCoordID);
        glVertexAttribPointer(textureCoordID, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    else
    {
        mVBOColors.Bind();
        GLuint colorID = shaderProgram->GetColorAttribute();
        glEnableVertexAttribArray(colorID);
        glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    if (mNeedNormal)
    {
        mVBONormals.Bind();
        GLuint normalID = shaderProgram->GetNormalAttribute();
        glEnableVertexAttribArray(normalID);
        glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
}
