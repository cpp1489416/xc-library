#include "ShadowShaderProgram.h"
#include <cassert>

void ShadowShaderProgram::AddThing(Thing * thing)
{
    thing->mNeedNormal = true;
    thing->mNeedTexture = false;
    thing->Create();
    thing->ChangeShaderProgram(this);
    mThings.push_back(thing);
}

void ShadowShaderProgram::DrawAllThings()
{
    mInFirstStep = false;
    for (auto i : mThings)
    {
        i->mNeedNormal = true;
        i->mNeedTexture = false;
        i->UpdateCurrentShaderProgram();
        mShadowTexture.Bind();
        i->Draw();
    }
}

Program * ShadowShaderProgram::GetCurrentProgram()
{
    if (mInFirstStep)
    {
        return &mFirstProgram;
    }
    else
    {
        return &mSecondProgram;
    }
}

void ShadowShaderProgram::SetModelMatrixFromThing(Thing * thing)
{
    if (mInFirstStep)
    {
        mFirstProgram.Bind();
        GLuint modelMatrixID = GetModelMatrixUniform();
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &(*thing->mTransform.GetMatrix())[0][0]);
    }
    else
    {
        mSecondProgram.Bind();
        GLuint modelMatrixID = GetModelMatrixUniform();
        glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &(*thing->mTransform.GetMatrix())[0][0]);

        GLuint lightModelMatrixID = GetLightModelMatrixUniform();
        glUniformMatrix4fv(lightModelMatrixID, 1, GL_FALSE, &(*thing->mTransform.GetMatrix())[0][0]);
    }
}

void ShadowShaderProgram::UpdateFromCamera(Camera * camera)
{
    mInFirstStep = false;
    camera->UpdateToShaderProgram(this);
}

void ShadowShaderProgram::UpdateFromLightCamera(Camera * camera)
{
    // first
    mInFirstStep = true;
    mFirstProgram.Bind();

    GLuint projectionID = GetProjectionMatrixUniform();
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &(*camera->GetProjectionMatrix())[0][0]);

    GLuint viewID = GetViewMatrixUniform();
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &(*camera->GetViewMatrix())[0][0]);

    // second
    mInFirstStep = false;
    mSecondProgram.Bind();

    GLuint lightProjectionID = GetLightProjectionMatrixUniform();
    glUniformMatrix4fv(lightProjectionID, 1, GL_FALSE, &(*camera->GetProjectionMatrix())[0][0]);

    GLuint lightViewID = GetLightViewMatrixUniform();
    glUniformMatrix4fv(lightViewID, 1, GL_FALSE, &(*camera->GetViewMatrix())[0][0]);

    glm::vec3 camPos = camera->mPosition;
    GLuint lightPositionID = GetLightPositionUniform();
    glUniform3f(lightPositionID, camPos[0], camPos[1], camPos[2]);
}

void ShadowShaderProgram::UpdateShadowTexture()
{
    mInFirstStep = true;
    mFBO.Bind();
    glViewport(0, 0, mWidth * mLargerFactor, mHeight * mLargerFactor);

    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);

    for (auto i : mThings)
    {
        i->mNeedNormal = false;
        i->mNeedTexture = false;
        i->UpdateCurrentShaderProgram();
        i->Draw();
    }

    glCullFace(GL_BACK);
    glViewport(0, 0, mWidth, mHeight);
    mFBO.Unbind();
}

void ShadowShaderProgram::ChangeSize(int width, int height)
{
    mWidth = width;
    mHeight = height;

    mShadowTexture.SetData(
        0,
        GL_DEPTH_COMPONENT,
        mWidth * mLargerFactor,
        mHeight * mLargerFactor,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        NULL);

    mFBO.Bind();
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        mShadowTexture.GetID(),
        0);

    glDrawBuffer(GL_NONE);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE)
    {
        assert(false);
    }

    mFBO.Unbind();

    UpdateShadowTexture();
}

void ShadowShaderProgram::OnCreate()
{
    mFBO.Create();
    mShadowTexture.Create();

    mFirstVS.CompileFromFile("Shaders/BasicVS.glsl");
    mFirstPS.CompileFromFile("Shaders/BasicPS.glsl");
    mFirstProgram.AddShader(&mFirstVS);
    mFirstProgram.AddShader(&mFirstPS);
    mFirstProgram.Link();

    mSecondVS.CompileFromFile("Shaders/ShadowVS.glsl");
    mSecondPS.CompileFromFile("Shaders/ShadowPS.glsl");
    mSecondProgram.AddShader(&mSecondVS);
    mSecondProgram.AddShader(&mSecondPS);
    mSecondProgram.Link();

    mInFirstStep = true;
}
