#pragma once 

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Technique;

class Camera
{
public:
    enum class TransformType
    {
        Aircraft, LandObject, Local
    };

public:
    Camera();

    void Reset();
    glm::mat4 * GetProjectionMatrix() { return &mProjectionMatrix; }
    glm::mat4 * GetViewMatrix() { return &mMatrix; }
    void SetPerspective(float angle, float near, float far);
    void SetViewportAspect(float aspect);
    void LookAt(float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upoZ);
    void LookTo(float eyeX, float eyeY, float eyeZ, float toX, float toY, float toZ, float upX, float upY, float upZ);
    void SetTransformType(TransformType type) { mTransformType = type; }
    void Pitch(float angle);
    void Yaw(float angle);
    void Roll(float angle);
    void Walk(float distance);
    void Strafe(float distance);
    void Fly(float distnace);
    void UpdateViewMatrix() { SetMatrix(); }
    void UpdateProjectionMatrix();
    void UpdateToTechnique(Technique * shaderPorgram);
    
public:
    TransformType mTransformType = TransformType::Local; 
    const bool mLeftHanded = true;
    const bool mOrthogonal = false;
    float mViewportAspect = 1.0f;
    float mNear = 0.01f;
    float mFar = 1000000.0f;
    float mAngle = 90.0f;
    glm::mat4 mProjectionMatrix;
    glm::mat4 mMatrix;
    glm::vec3 mPosition = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 mXVector = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 mYVector = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 mZVector = glm::vec3(0.0f, 0.0f, 1.0f);

private:
    void SetMatrix();
};  