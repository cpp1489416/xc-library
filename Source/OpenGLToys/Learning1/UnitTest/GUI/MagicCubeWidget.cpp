#include "MagicCubeWidget.h"
#include <qevent.h>
#include "qinputdialog.h"

using namespace MagicCubes;

MagicCubeWidget::MagicCubeWidget(QWidget *parent)
    : GLWindowsWidget(parent)
{
    QTimer * timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MagicCubeWidget::Timeout);
    timer->start(500);

    connect(&mMagicCube, &MagicCube::UpdatedSignal, this, &MagicCubeWidget::OnMagicCubeUpdated);
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
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
}

void MagicCubeWidget::OnResizeOpenGL(int width, int height)
{
    glViewport(0, 0, width, height);
    mCamera.SetViewportAspect((float)width / height);
}

void MagicCubeWidget::OnPaintOpenGL()
{
    //mMagicCube.Update();
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
    if (mMagicCube.IsRotationFinished())
    {
        static bool bigger = true;

        if (bigger)
        {
            mRotationStates.push(RotationState::GetRandomRotationState(mMagicCube.GetCountRows()));
            mMagicCube.RequireRotationState(mRotationStates.top());

            if (mRotationStates.size() > 50)
            {
                bigger = false;
            }
        }
        else
        {
            if (mRotationStates.empty())
            {
                return;
            }

            mRotationStates.top() = mRotationStates.top().GetOppositeRotationState();
            mMagicCube.RequireRotationState(mRotationStates.top());
            mRotationStates.pop();
        }
        update();
    }

}
