#include "MagicCubeWidget.h"
#include <qevent.h>
#include "qinputdialog.h"

using namespace MagicCubes;

MagicCubeWidget::MagicCubeWidget(QWidget *parent)
    : GLWindowsWidget(parent)
{
    QTimer * timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MagicCubeWidget::Timeout);
    timer->start(100);
}

MagicCubeWidget::~MagicCubeWidget()
{
}

void MagicCubeWidget::OnInitializeOpenGL()
{
    mCamera.LookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
    mCamera.SetPerspective(60, 0.1, 1000);

    mBasicTechnique.Create();

    mBasicTechnique.AddThing(&mAnchor);
    mAnchor.mTransform.mScale = glm::vec3(10, 10, 10);

    mBasicTechnique.AddThing(&mMagicCube);
    //mBasicTechnique.AddThing(&mCube);

    glClearColor(0, 0.5, 0, 1);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW); // default
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    mMagicCube.SetRotationState(RotationState(Face::Front, Clockwise::CCW, 0, 2));
    mMagicCube.SetRotationState(RotationState(Face::Right, Clockwise::CCW, 2));
    mMagicCube.SetRotationState(RotationState(Face::Front, Clockwise::CCW, 3));
    mMagicCube.SetRotationState(RotationState(Face::Right, Clockwise::CCW, 2));
    mMagicCube.SetRotationState(RotationState(Face::Up, Clockwise::CCW, 1, 3));
    mMagicCube.SetRotationState(RotationState(Face::Up, Clockwise::CCW, 0, 0));
    //   mMagicCube.mTransform.mPosition = glm::vec3(3, 3, 0);
}

void MagicCubeWidget::OnResizeOpenGL(int width, int height)
{
    glViewport(0, 0, width, height);
    mCamera.SetViewportAspect((float)width / height);
}

void MagicCubeWidget::OnPaintOpenGL()
{
    mMagicCube.Update();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDisable(GL_CULL_FACE);

    mBasicTechnique.UpdateFromCamera(&mCamera);
    glDepthMask(GL_TRUE);
    //  glDisable(GL_CULL_FACE);
    mBasicTechnique.DrawAllThings();
}


void MagicCubeWidget::mousePressEvent(QMouseEvent * event)
{
    if (event->buttons() | Qt::LeftButton)
    {
        mLastPosition = event->screenPos();
    }
}

void MagicCubeWidget::mouseMoveEvent(QMouseEvent * event)
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

void MagicCubeWidget::keyPressEvent(QKeyEvent * event)
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
        break;
    }
    default:
        break;
    }

    update();
}

void MagicCubeWidget::Timeout()
{
    mMagicCube.SetRotationState(RotationState::GetRandomRotationState(mMagicCube.GetCountRows()));
    update();
}
