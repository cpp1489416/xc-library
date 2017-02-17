#include "Cube.h"

void Cube::OnCreate()
{
    GLfloat skyboxVertices[] = {
        // 背面
        -1.0f, -1.0f, 1.0f, 		// A
        -1.0f, 1.0f, 1.0f,	// B
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// C
        1.0f, -1.0f, 1.0f,		// D
        -1.0f, -1.0f, 1.0f,		// A

                                        // 左侧面
        -1.0f, -1.0f, 1.0f,		// E
        -1.0f, -1.0f, -1.0f,	// B
        -1.0f, 1.0f, -1.0f,		// A
        -1.0f, 1.0f, -1.0f,		// A
        -1.0f, 1.0f, 1.0f,		// F
        -1.0f, -1.0f, 1.0f,		// E

                                        // 右侧面
        1.0f, -1.0f, -1.0f,		// C
        1.0f, -1.0f, 1.0f,		// G
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, -1.0f,		// D
        1.0f, -1.0f, -1.0f,		// C

                                        // 正面
        -1.0f, -1.0f, -1.0f,  // E
        1.0f, -1.0f, -1.0f,  // F
        1.0f, 1.0f, -1.0f,  // H
        1.0f, 1.0f, -1.0f,  // H
        -1.0f, 1.0f, -1.0f,  // G
        -1.0f, -1.0f, -1.0f,  // E

                             // 顶面
        -1.0f, 1.0f, -1.0f,  // A
        1.0f, 1.0f, -1.0f,  // D
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        -1.0f, 1.0f, 1.0f,  // F
        -1.0f, 1.0f, -1.0f,  // A

                             // 底面
        -1.0f, -1.0f, 1.0f,  // B
        1.0f, -1.0f, 1.0f,   // E
        1.0f, -1.0f, -1.0f,    // G
        1.0f, -1.0f, -1.0f,    // G
        -1.0f, -1.0f, -1.0f,   // C
        -1.0f, -1.0f, 1.0f,  // B
    };

    GLfloat normals[] =
    {
        // 背面
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        // 左侧面, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        // 右侧面

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        // 正面

        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,
        // 顶面

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        // 底面

        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
    };

    GLfloat colors[] = {
        // 背面
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,	// B
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// D
        1.0f, 1.0f, 1.0f,		// A

                                        // 左侧面
        1.0f, 1.0f, 1.0f,		// E
        1.0f, 1.0f, 1.0f,	// B
        1.0f, 1.0f, 1.0f,		// A
        1.0f, 1.0f, 1.0f,		// A
        1.0f, 1.0f, 1.0f,		// F
        1.0f, 1.0f, 1.0f,		// E

                                        // 右侧面
        1.0f, 1.0f, 1.0f,		// C
        1.0f, 1.0f, 1.0f,		// G
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, 1.0f,		// H
        1.0f, 1.0f, 1.0f,		// D
        1.0f, 1.0f, 1.0f,		// C

                                        // 正面
        1.0f, 1.0f, 1.0f,  // E
        1.0f, 1.0f, 1.0f,  // F
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // G
        1.0f, 1.0f, 1.0f,  // E

                           // 顶面
        1.0f, 1.0f, 1.0f,  // A
        1.0f, 1.0f, 1.0f,  // D
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // H
        1.0f, 1.0f, 1.0f,  // F
        1.0f, 1.0f, 1.0f,  // A

                           // 底面
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

void Cube::OnChangeShaderProgram(ShaderProgram * shaderProgram)
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
        GLuint normalAttribute = mShaderProgram->GetNormalAttribute();
        mVBONormals.Bind();
        glEnableVertexAttribArray(normalAttribute);
        glVertexAttribPointer(normalAttribute, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    }
}