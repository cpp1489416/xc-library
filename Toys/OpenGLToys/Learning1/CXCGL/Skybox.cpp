#include "Skybox.h"
#include <QImage>
#include "../FileLoaders/DDSFileLoader.h"

namespace
{
    /* rubbish
    static GLenum indexToTargetTexture[] =
    {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
    };
    */
}

void Skybox::MShaderProgram::OnCreate()
{
    mVertexShader.CompileFromFile("Shaders/SkyboxVertexShader.glsl");
    mFragmentShader.CompileFromFile("Shaders/SkyboxFragmentShader.glsl");
    mProgram.AddShader(&mVertexShader);
    mProgram.AddShader(&mFragmentShader);
}

Skybox::Skybox()
{
    mPicturePaths[0] = "Textures/CubeMapPX.png";
    mPicturePaths[1] = "Textures/CubeMapNX.png";
    mPicturePaths[2] = "Textures/CubeMapPY.png";
    mPicturePaths[3] = "Textures/CubeMapNY.png";
    mPicturePaths[4] = "Textures/CubeMapPZ.png";
    mPicturePaths[5] = "Textures/CubeMapNZ.png";
}

void Skybox::SetCamera(Camera * camera)
{
    mCamera = camera;
}

void Skybox::Create()
{
    mShaderProgram.Create();
    mShaderProgram.GetCurrentProgram()->Bind();
    LoadCubeMapTexture();
    CreateVAOAndVBOs();
}

void Skybox::Draw()
{
    mShaderProgram.GetCurrentProgram()->Bind();

    // disabe depth test to make sure every point rendered
    glDepthMask(GL_FALSE);
    // glEnable(GL_TEXTURE_2D); 

    // projection matrix
    glUniformMatrix4fv(mShaderProgram.GetProjectionMatrixUniform(), 1, GL_FALSE, &(*mCamera->GetProjectionMatrix())[0][0]);

    // the View matrix is very different
    glm::mat4 viewMatrix = *mCamera->GetViewMatrix();
    viewMatrix[3][0] = viewMatrix[3][1] = viewMatrix[3][2] = 0.0f; // can rotate, cannot translate
    glUniformMatrix4fv(mShaderProgram.GetViewMatrixUniform(), 1, GL_FALSE, &viewMatrix[0][0]);

    for (int i = 0; i < 6; ++i)
    {
        mVAOs[i].Bind();
        glBindTexture(GL_TEXTURE_2D, mTextureIDs[i]); // the cubemap vertex
                             
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
    }
    // make sure depth is enabled
    glDepthMask(GL_TRUE);
}

void Skybox::LoadCubeMapTexture()
{
    glEnable(GL_TEXTURE_2D);

    glGenTextures(6, mTextureIDs);

    for (int i = 0; i < 6; i++)
    {
        mFileLoader.Create(mPicturePaths[i]);
        glBindTexture(GL_TEXTURE_2D, mTextureIDs[i]);
        glTexImage2D(
            GL_TEXTURE_2D,
            0, // level
            mFileLoader.GetFormat(), // GL_RGBA
            mFileLoader.GetWidth(),
            mFileLoader.GetHeight(),
            0, // border
            mFileLoader.GetFormat(), // GL_RGBA
            mFileLoader.GetDataType(), // GL_UNSIGNED_BYTE
            mFileLoader.GetData());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }
}

void Skybox::CreateVAOAndVBOs()
{
    mShaderProgram.GetCurrentProgram()->Bind();
    GLfloat vertices[][20] =
    {
        {   // right face, +X, CCW 
            1, -1, 1, 0, 0, // left down
            1, -1, -1, 1, 0, // right down
            1, 1, -1, 1, 1, // right up
            1, 1, 1, 0, 1, // left up
        },

        { // left face, -X, CCW
            -1, -1, -1, 0, 0,
            -1, -1, 1, 1, 0,
            -1, 1, 1, 1, 1,
            -1, 1, -1, 0, 1,
        },

        { // up face, +Y, CCW
            -1, 1, 1, 0, 0,
            1, 1, 1, 1, 0,
            1, 1, -1, 1, 1,
            -1, 1, -1, 0, 1,
        },

        { // down face, -Y, CCW
            -1, -1, -1, 0, 0,
            1, -1, -1, 1, 0,
            1, -1, 1, 1, 1,
            -1, -1, 1, 0, 1,
        },

        { // front face, +Z, CCW
            -1, -1, 1, 0, 0,
            1, -1, 1, 1, 0,
            1, 1, 1, 1, 1,
            -1, 1, 1, 0, 1,
        },

        { // back face, -Z, CCW
            1, -1, -1, 0, 0,
            -1, -1, -1, 1, 0,
            -1, 1, -1, 1, 1,
            1, 1, -1, 0, 1,
        },
    };

    GLushort indices[] =
    {
        0, 1, 2,
        2, 3, 0,
    };


    for (int i = 0; i < 6; ++i)
    {
        mVBOPositions[i] = Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
        mVBOTextureCoords[i] = Buffer(GL_TEXTURE_BUFFER, GL_STATIC_DRAW);

        mVAOs[i].Bind();
        mVBOPositions[i].Bind();
        mVBOPositions[i].SetData(vertices[i], sizeof(vertices[i]));
        glEnableVertexAttribArray(mShaderProgram.GetPositionAttribute());
        glVertexAttribPointer(mShaderProgram.GetPositionAttribute(), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), NULL);

        // return;
        mVBOTextureCoords[i].Bind();
        mVBOTextureCoords[i].SetData(vertices[i], sizeof(vertices[i]));
        glEnableVertexAttribArray(mShaderProgram.GetTextureCoordAttribute());
        glVertexAttribPointer(mShaderProgram.GetTextureCoordAttribute(), 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (void *)(3 * sizeof(GL_FLOAT)));

        mEBO.Bind();
        mEBO.SetData(indices, sizeof(indices));
    }
}
