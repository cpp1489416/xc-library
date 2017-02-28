#pragma once

#include <qwidget.h>
#include "../../QTGUI/GLWindowsWidget.h"
#include "../../Techniques/BasicTechnique.h"
#include "../MagicCube.h"
#include "Things/Cube.h"

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
    void mousePressEvent(QMouseEvent * event) override final;
    void mouseMoveEvent(QMouseEvent * event) override final;
    void keyPressEvent(QKeyEvent *event) override final;

private:
    Cube mCube;
    Camera mCamera;
    BasicTechnique mBasicTechnique;
    MagicCube::MagicCube mMagicCube;
    QPointF mLastPosition;
};