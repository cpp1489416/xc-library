#pragma once

#include <qwidget.h>
#include "../../QTGUI/GLWindowsWidget.h"
#include "../../Techniques/BasicTechnique.h"
#include "../MagicCube.h"

class MagicCubeWidght : public GLWindowsWidget
{
    Q_OBJECT

public:
    MagicCubeWidght(QWidget *parent);
    ~MagicCubeWidght();

protected:
    void OnInitializeOpenGL() override;
    void OnResizeOpenGL(int width, int height) override;
    void OnPaintOpenGL() override;

private:
    Camera mCamera;
    BasicTechnique mBasicTechnique;
    MagicCube::MagicCube mMagicCube;
};
