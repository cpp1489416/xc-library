#include "Quad.h"

void Quad::OnCreate()
{
    GLfloat positions[] =
    {
        -1, -1, 0,
        1, -1, 0,
        1, 1, 0,

        1, 1, 0,
        -1, 1, 0,
        -1, -1, 0,
    };

    GLfloat textureCoords[] =
    {
        0, 0,
        1, 0,
        1, 1,

        1, 1,
        0, 1,
        0, 0,
    };

    GLfloat colors[] =
    {
        1, 1, 1,
        1, 1, 1,
        1, 1, 1,

        1, 1, 1,
        1, 1, 1,
        1, 1, 1,
    };

    GLfloat normals[] =
    {
        0, 0, -1,
        0, 0, -1,
        0, 0, -1,

        0, 0, -1,
        0, 0, -1,
        0, 0, -1,
    };


    mVBOPositions.Bind();
    mVBOPositions.SetData(positions, sizeof(positions));

    mVBOColors.Bind();
    mVBOColors.SetData(colors, sizeof(colors));

    mVBOTextureCoords.Bind();
    mVBOTextureCoords.SetData(textureCoords, sizeof(textureCoords));

    mVBOnormals.Bind();
    mVBOnormals.SetData(normals, sizeof(normals));
}

void Quad::OnDraw()
{
    mVAO.Bind();

    if (mNeedTexture)
    {
        glBindTexture(GL_TEXTURE_2D, mShaderProgram->GetTextureID());
    }

    glDrawArrays(GL_TRIANGLES, 0, 6);
}


void Quad::OnChangeShaderProgram(ShaderProgram *shaderProgram)
{
    mVAO.Bind();

    GLuint positionID = shaderProgram->GetPositionAttribute();
    mVBOPositions.Bind();
    glEnableVertexAttribArray(positionID);
    glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    if (mNeedTexture)
    {
        GLuint textureCoordID = shaderProgram->GetTextureCoordAttribute();
        mVBOTextureCoords.Bind();
        glEnableVertexAttribArray(textureCoordID);
        glVertexAttribPointer(textureCoordID, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    }
    else
    {
        GLuint colorID = shaderProgram->GetColorAttribute();
        mVBOColors.Bind();
        glEnableVertexAttribArray(colorID);
        glVertexAttribPointer(colorID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    if (mNeedNormal)
    {
        GLuint normalID = shaderProgram->GetNormalAttribute();
        mVBOnormals.Bind();
        glEnableVertexAttribArray(normalID);
        glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
}