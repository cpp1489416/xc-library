#pragma once

#include <qwidget.h>
#include "../../QTGUI/GLWindowsWidget.h"
#include "../../Techniques/BasicTechnique.h"
#include "../MagicCubes/MagicCube.h"
#include "Things/Cube.h"
#include "Things/Anchor.h"
#include <stack>

class MagicCubeWidget : public GLWindowsWidget
{
    Q_OBJECT

public:
    MagicCubeWidget(QWidget *parent);
    ~MagicCubeWidget();

protected:
    void OnInitializeOpenGL() override;
    void OnResizeOpenGL(int width, int height) override;
    void OnPaintOpenGL() override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void Timeout();

private:
    Cube mCube;
    Camera mCamera;
    BasicTechnique mBasicTechnique;
    MagicCubes::MagicCube mMagicCube;
    Anchor mAnchor;
    QPointF mLastPosition;
    std::stack<MagicCubes::RotationState> mRotationStates;
};
