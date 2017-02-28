#include "GLHouseWidget.h"
#include <glm/glm.hpp>
#include <algorithm>
#include <QMouseEvent>
#include "../Things/MengerSpongeCube.h"
#include "../Things/Cube.h"

GLHouseWidget::GLHouseWidget(QWidget *parent) :
    GLWindowsWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    mTimer = new QTimer();
    connect(mTimer, &QTimer::timeout, this, &GLHouseWidget::UpdateScene);
    // mTimer->start(30);
}

void GLHouseWidget::DropLightCamera(float value)
{
    static float curY = 200;
    curY -= 1.0;
    mLightCamera.LookAt(50, curY, -50, 0, 0, 0, 0, 1, 0);
    mLightPositionCube.mTransform.mPosition = mLightCamera.mPosition;
    mShadowTechnique.UpdateFromLightCamera(&mLightCamera);
    mShadowTechnique.UpdateShadowTexture();
    update();
}

void GLHouseWidget::OnInitializeOpenGL()
{
    mCamera.LookAt(0, 0, -13, 0, 0, 0, 0, 1, 0);
    mCamera.SetPerspective(60, 0.1, 300);

    mLightCamera.LookAt(50, 50, -50, 0, 0, 0, 0, 1, 0);
    mLightCamera.SetPerspective(60, 0.1, 3000);

    mPointLight.mPosition = mLightCamera.mPosition;
    mPointLight.mIntensities = glm::vec3(1, 1, 0.79);

    mSkybox.SetCamera(&mCamera);
    mSkybox.Create();

    mBasicTechnique.Create();

    mShadowTechnique.mLargerFactor = 1;
    mShadowTechnique.Create();
    mShadowTechnique.UpdateFromLightCamera(&mLightCamera);

    mLightingTechnique.Create();
    mLightingTechnique.SetPointLight(&mPointLight);

    mTextureTechnique.Create();
    mTextureTechnique.SetPicturePath("Textures/EarthCylindricalMap.jpg");

    mTextureLightingTechnique.Create();
    mTextureLightingTechnique.SetPointLight(&mPointLight);
    mTextureLightingTechnique.SetPicturePath("Textures/EarthCylindricalMap.jpg");

    mBasicTechnique.AddThing(&mAnchor);

    mTextureSphere.mCountColumns = 36;
    mTextureSphere.mCountRows = 36;
    mTextureTechnique.AddThing(&mTextureSphere);
    mTextureSphere.mTransform.mScale = glm::vec3(3, 3, 3);

    mShadowTechnique.AddThing(&mCube);
    mCube.mTransform.mPosition = glm::vec3(8, -10, 0);
    mCube.mTransform.mRotation = glm::vec3(0, 0, 0);
    mCube.mTransform.mScale = glm::vec3(3, 3, 3);

    mShadowTechnique.AddThing(&mCube2);
    mCube2.mTransform.mPosition = glm::vec3(2, -5, 3);
    mCube2.mTransform.mRotation = glm::vec3(0, 0, 0);
    mCube2.mTransform.mScale = glm::vec3(2, 1, 3);

    mBasicTechnique.AddThing(&mLightPositionCube);
    mLightPositionCube.mTransform.mPosition = mPointLight.mPosition;
    mLightPositionCube.mTransform.mScale = glm::vec3(0.1, 0.1, 0.1);

    mSphere.mCountRows = mSphere.mCountColumns = 36;
    mShadowTechnique.AddThing(&mSphere);
    mSphere.mTransform.mPosition = glm::vec3(-9, -10, 7);
    mSphere.mTransform.mScale = glm::vec3(3, 3, 3);

    mShadowTechnique.AddThing(&mQuadBottom);
    mQuadBottom.mTransform.mScale = glm::vec3(23, 23, 23);
    mQuadBottom.mTransform.mRotation = glm::vec3(90, 0, 0);
    mQuadBottom.mTransform.mPosition = glm::vec3(0, -15, 0);

    mShadowTechnique.AddThing(&mQuadBack);
    mQuadBack.mTransform.mScale = glm::vec3(23, 23, 23);
    mQuadBack.mTransform.mRotation = glm::vec3(0, 0, 0);
    mQuadBack.mTransform.mPosition = glm::vec3(-0, 0, 15);

    mShadowTechnique.AddThing(&mQuadLeft);
    mQuadLeft.mTransform.mScale = glm::vec3(23, 23, 23);
    mQuadLeft.mTransform.mRotation = glm::vec3(0, -90, 0);
    mQuadLeft.mTransform.mPosition = glm::vec3(-15, 0, 0);

    glClearColor(0, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW); // default
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    mShadowTechnique.UpdateFromLightCamera(&mLightCamera);
}

void GLHouseWidget::OnPaintOpenGL()
{
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    mCamera.UpdateToTechnique(&mBasicTechnique);
    mCamera.UpdateToTechnique(&mTextureTechnique);
    mCamera.UpdateToTechnique(&mTextureLightingTechnique);
    mShadowTechnique.UpdateFromCamera(&mCamera);
   
    mSkybox.Draw();
    mBasicTechnique.DrawAllThings();
    mTextureTechnique.DrawAllThings();
    mShadowTechnique.DrawAllThings();
}

void GLHouseWidget::OnResizeOpenGL(int width, int height)
{
    glViewport(0, 0, width, height);
    mCamera.SetViewportAspect((float)width / height);

    mLightCamera.SetViewportAspect((float)width / height);
    mShadowTechnique.UpdateFromLightCamera(&mLightCamera);
     mShadowTechnique.ChangeSize(width, height); // change size and update texture
}

void GLHouseWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->buttons() | Qt::LeftButton)
    {
        mLastPosition = event->screenPos();
    }
}

void GLHouseWidget::mouseMoveEvent(QMouseEvent * event)
{
    static float d = 0.01f;
    if (event->button() | Qt::MouseButton::LeftButton)
    {
        QPointF curPos = event->screenPos();
        float dx = curPos.x() - mLastPosition.x();
        float dy = curPos.y() - mLastPosition.y();
        mCamera.Pitch(dy * d);
        mCamera.Yaw(dx * d);

        mLastPosition = curPos;
        update();
    }
}

void GLHouseWidget::keyPressEvent(QKeyEvent * event)
{
    static const float d = 1.0f;
    switch (event->key())
    {
    case Qt::Key_W:
    {
        mCamera.Walk(d);
        break;
    }
    case Qt::Key_S:
    {
        mCamera.Walk(-d);
        break;
    }
    case Qt::Key_A:
    {
        mCamera.Strafe(-d);
        break;
    }
    case Qt::Key_D:
    {
        mCamera.Strafe(d);
        break;
    }
    case Qt::Key_Up:
    {
        mCamera.Fly(d);
        break;
    }
    case Qt::Key_Down:
    {
        mCamera.Fly(-d);
        break;
    }
    case Qt::Key_Q:
    {
        DropLightCamera(-d);
        break;
    }
    default:
        break;
    }

    update();
}

void GLHouseWidget::UpdateScene()
{
    mCamera.Yaw(0.1);
    update();
}
