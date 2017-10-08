#include "Cube.h"

void Cube::OnCreate()
{
    GLfloat skyboxVertices[] =
    {
        -1.0f, -1.0f, 1.0f, 		// A
        -1.0f, 1.0f, 1.0f,	// B
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// C
        1.0f, -1.0f, 1.0f,		// D
        -1.0f, -1.0f, 1.0f,		// A

        -1.0f, -1.0f, 1.0f,		// E
        -1.0f, -1.0f, -1.0f,	// B
        -1.0f, 1.0f, -1.0f,		// A
        -1.0f, 1.0f, -1.0f,		// A
        -1.0f, 1.0f, 1.0f,		// F
        -1.0f, -1.0f, 1.0f,		// E

        1.0f, -1.0f, -1.0f,		// C
        1.0f, -1.0f, 1.0f,		// G
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, -1.0f,		// D
        1.0f, -1.0f, -1.0f,		// C

        -1.0f, -1.0f, -1.0f,  // E
        1.0f, -1.0f, -1.0f,  // F
        1.0f, 1.0f, -1.0f,  // H
        1.0f, 1.0f, -1.0f,  // H
        -1.0f, 1.0f, -1.0f,  // G
        -1.0f, -1.0f, -1.0f,  // E

        -1.0f, 1.0f, -1.0f,  // A
        1.0f, 1.0f, -1.0f,  // D
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        -1.0f, 1.0f, 1.0f,  // F
        -1.0f, 1.0f, -1.0f,  // A

        -1.0f, -1.0f, 1.0f,  // B
        1.0f, -1.0f, 1.0f,   // E
        1.0f, -1.0f, -1.0f,    // G
        1.0f, -1.0f, -1.0f,    // G
        -1.0f, -1.0f, -1.0f,   // C
        -1.0f, -1.0f, 1.0f,  // B
    };

    GLfloat normals[] =
    {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };

    GLfloat colors[] = {
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,	// B
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// D
        1.0f, 1.0f, 1.0f,		// A

        1.0f, 1.0f, 1.0f,		// E
        1.0f, 1.0f, 1.0f,	// B
        1.0f, 1.0f, 1.0f,		// A
        1.0f, 1.0f, 1.0f,		// A
        1.0f, 1.0f, 1.0f,		// F
        1.0f, 1.0f, 1.0f,		// E

        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// G
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, 1.0f,		// D
        1.0f, 1.0f, 1.0f,		// C

        1.0f, 1.0f, 1.0f,  // E
        1.0f, 1.0f, 1.0f,  // F
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // G
        1.0f, 1.0f, 1.0f,  // E

        1.0f, 1.0f, 1.0f,  // A
        1.0f, 1.0f, 1.0f,  // D
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // F
        1.0f, 1.0f, 1.0f,  // A

        1.0f, 1.0f, 1.0f,  // B
        1.0f, 1.0f, 1.0f,   // E
        1.0f, 1.0f, 1.0f,    // G
        1.0f, 1.0f, 1.0f,    // G
        1.0f, 1.0f, 1.0f,   // C
        1.0f, 1.0f, 1.0f,  // B
    };

    mVBOPositions.Bind();
    mVBOPositions.SetData(skyboxVertices, sizeof(skyboxVertices));

    mVBOColors.Bind();
    mVBOColors.SetData(colors, sizeof(colors));

    mVBONormals.Bind();
    mVBONormals.SetData(normals, sizeof(normals));
}

void Cube::OnDraw()
{
    mVAO.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::OnChangeTechnique(Technique * shaderProgram)
{
    mVAO.Destroy();
    mVAO.Bind();

    GLuint mPositionAttribute = shaderProgram->GetPositionAttribute();
    mVBOPositions.Bind();
    glEnableVertexAttribArray(mPositionAttribute);
    glVertexAttribPointer(mPositionAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    if (mNeedTexture)
    {

    }
    else
    {
        GLuint mColorAttribute = shaderProgram->GetColorAttribute();
        mVBOColors.Bind();
        glEnableVertexAttribArray(mColorAttribute);
        glVertexAttribPointer(mColorAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }

    if (mNeedNormal)
    {
        GLuint normalAttribute = mTechnique->GetNormalAttribute();
        mVBONormals.Bind();
        glEnableVertexAttribArray(normalAttribute);
        glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
}
