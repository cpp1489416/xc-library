    #pragma once

#include <gl/glew.h>
#include "ShaderProgram.h"
#include "Camera.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "../FileLoaders/ImageFileLoader.h"

class Skybox
{
public:
    class MShaderProgram : public ShaderProgram
    {
    public:
        Program * GetCurrentProgram() override { return &mProgram; }
        GLuint GetProjectionMatrixUniform() override { return GetUniformLocation("projection"); }
        GLuint GetViewMatrixUniform() override { return GetUniformLocation("view"); }
        GLuint GetPositionAttribute() override { return GetAttributeLocation("position"); }
        
    public:
        GLuint GetSkyboxUniform() { return GetUniformLocation("skybox"); }
        GLuint GetTextureCoordAttribute() { return GetAttributeLocation("textureCoord"); }

    protected:
        virtual void OnCreate() override;

    private:
        Program mProgram;
        Shader mVertexShader = Shader(GL_VERTEX_SHADER);
        Shader mFragmentShader = Shader(GL_FRAGMENT_SHADER);
    };

public:
    Skybox();

    void SetCamera(Camera *camera);
    void Create();
    void Draw();

public:
    const char *mPicturePaths[6];

private:
    void LoadCubeMapTexture();
    void CreateVAOAndVBOs();

public:
    MShaderProgram mShaderProgram;
    Camera * mCamera;
    VertexArrayObject mVAOs[6];
    Buffer mEBO = Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    Buffer mVBOPositions[6];
    Buffer mVBOTextureCoords[6];
    GLenum mTextureIDs[6];
    ImageFileLoader mFileLoader;
};