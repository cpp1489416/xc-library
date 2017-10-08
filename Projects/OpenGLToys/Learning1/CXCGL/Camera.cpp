#include "Camera.h"
#include "Technique.h"
#include <algorithm>

namespace
{
    static const float PI = 3.14f;
    static float factorPIToAngle = PI / 180.0f;
}

Camera::Camera()
{
    SetMatrix();
    UpdateProjectionMatrix();
}

void Camera::Reset()
{
    SetMatrix();
}

void Camera::SetPerspective(float angle, float near, float far)
{
    mAngle = angle;
    mNear = near;
    mFar = far;

    UpdateProjectionMatrix();
}

void Camera::SetViewportAspect(float aspect)
{
    mViewportAspect = aspect;
    UpdateProjectionMatrix();
}

void Camera::LookAt(float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ)
{
    // mMatrix = glm::lookAtLH(glm::vec3(eyeX, eyeY, eyeZ), glm::vec3(targetX, targetY, targetZ), glm::vec3(upX, upY, upZ));
    // return;
    mPosition = glm::vec3(eyeX, eyeY, eyeZ);

    glm::vec3 target = glm::vec3(targetX, targetY, targetZ);
    glm::vec3 up = glm::vec3(upX, upY, upZ);

    mZVector = target - mPosition;
    mZVector = glm::normalize(mZVector);

    mXVector = glm::cross(up, mZVector);
    mXVector = glm::normalize(mXVector);

    mYVector = glm::cross(mZVector, mXVector);
    mYVector = glm::normalize(mYVector);

    SetMatrix();
}

void Camera::LookTo(float eyeX, float eyeY, float eyeZ, float toX, float toY, float toZ, float upX, float upY, float upZ)
{
}

void Camera::Pitch(float angle)
{
    glm::mat4 rm(1.0f);
    if (mTransformType == TransformType::Local)
    {
        rm = glm::rotate(rm, angle, mXVector);
        mPosition = glm::vec4(rm * glm::vec4(mPosition, 1));
    }
    else if (mTransformType == TransformType::Aircraft)
    {
        //    rm.rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
    }
    else
    {
        //    rm.rotate(angle, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    mYVector = rm * glm::vec4(mYVector, 1.0f);
    mZVector = rm * glm::vec4(mZVector, 1.0f);
    SetMatrix();
}

void Camera::Yaw(float angle)
{
    glm::mat4 rm(1.0f);
    if (mTransformType == TransformType::Local)
    {
        rm = glm::rotate(rm, angle, mYVector);
        mPosition = rm * glm::vec4(mPosition, 1.0f);
    }
    else if (mTransformType == TransformType::Aircraft)
    {
        // rm.rotate(angle, glm::vec3(0, 1, 0));
    }
    else
    {

    }

    mXVector = rm * glm::vec4(mXVector, 1.0f);
    mZVector = rm * glm::vec4(mZVector, 1.0f);

    SetMatrix();
}

void Camera::Roll(float angle)
{
    glm::mat4 rm(1.0f);
    if (mTransformType == TransformType::Local)
    {
        rm = glm::rotate(rm, angle, mZVector);
        mPosition = rm * glm::vec4(mPosition, 1.0f);
    }
    else if (mTransformType == TransformType::Aircraft)
    {
        // rm.rotate(angle, glm::vec3(0, 0, 1));
    }
    else
    {

    }

    mXVector = rm * glm::vec4(mXVector, 1.0f);
    mYVector = rm * glm::vec4(mYVector, 1.0f);

    SetMatrix();
}

void Camera::Walk(float distance)
{
    if (mTransformType == TransformType::LandObject)
    {
        mPosition += distance * glm::vec3(mZVector[0], 0.0f, mZVector[2]);
    }
    else
    {
        mPosition += distance * mZVector;
    }

    SetMatrix();
}

void Camera::Strafe(float distance)
{
    mPosition += distance * mXVector;
    SetMatrix();
}

void Camera::Fly(float distance)
{
    mPosition += distance * mYVector;
    SetMatrix();
}

void Camera::SetMatrix()
{
   // return;
    float x = -glm::dot(mXVector, mPosition);
    float y = -glm::dot(mYVector, mPosition);
    float z = -glm::dot(mZVector, mPosition);

    mMatrix[0][0] = mXVector[0];
    mMatrix[1][0] = mXVector[1];
    mMatrix[2][0] = mXVector[2];
    mMatrix[3][0] = x;

    mMatrix[0][1] = mYVector[0];
    mMatrix[1][1] = mYVector[1];
    mMatrix[2][1] = mYVector[2];
    mMatrix[3][1] = y; //-mPosition[1];

    mMatrix[0][2] = mZVector[0];
    mMatrix[1][2] = mZVector[1];
    mMatrix[2][2] = mZVector[2];
    mMatrix[3][2] = z; //-mPosition[2];

    mMatrix[0][3] = 0.0f;
    mMatrix[1][3] = 0.0f; // mZVector[1];
    mMatrix[2][3] = 0.0f; // mZVector[2];
    mMatrix[3][3] = 1.0f;

}

void Camera::UpdateProjectionMatrix()
{
    if (mOrthogonal)
    {
        // mProjectionMatrix.setToIdentity();
    }
    else
    {
      //  mProjectionMatrix = glm::perspectiveLH(mAngle * factorPIToAngle, mViewportAspect, mNear, mFar);
 //       return;
        mProjectionMatrix = glm::mat4(1.0f);
        // mProjectionMatrix.perspective(mAngle, mViewportAspect, mNear, mFar);
        // return;
        float a = std::tan(mAngle * factorPIToAngle / 2.0f);
        float b = mViewportAspect;
        float f = mFar;
        float n = mNear;

        mProjectionMatrix[0][0] = 1.0f / (a * b);
        mProjectionMatrix[1][1] = 1.0f / a;
        mProjectionMatrix[2][2] = f / (f - n);
        mProjectionMatrix[3][2] = -2.0f * f * n / (float)(f - n);
        mProjectionMatrix[2][3] = 1.0f;
        
 //       glm::transpose(mProjectionMatrix);
    }
}

void Camera::UpdateToTechnique(Technique * shaderPorgram)
{
    shaderPorgram->GetCurrentProgram()->Bind();
    GLuint projectionID = shaderPorgram->GetProjectionMatrixUniform();
    GLuint viewID = shaderPorgram->GetViewMatrixUniform();
    glUniformMatrix4fv(projectionID, 1, GL_FALSE, &mProjectionMatrix[0][0]);
    glUniformMatrix4fv(viewID, 1, GL_FALSE, &mMatrix[0][0]);
}
