#include "MagicCubeWidght.h"

MagicCubeWidght::MagicCubeWidght(QWidget *parent)
    : GLWindowsWidget(parent)
{
}

MagicCubeWidght::~MagicCubeWidght()
{
}

void MagicCubeWidght::OnInitializeOpenGL()
{
    mCamera.LookAt(0, 0, 14, 0, 0, 0, 0, 1, 0);
    mCamera.SetPerspective(60, 0.1, 1000);

    mBasicTechnique.Create();

    mBasicTechnique.AddThing(&mMagicCube);
}

void MagicCubeWidght::OnResizeOpenGL(int width, int height)
{
    mCamera.SetViewportAspect((float)width / height);
}

void MagicCubeWidght::OnPaintOpenGL()
{
    mBasicTechnique.UpdateFromCamera(&mCamera);
    mBasicTechnique.DrawAllThings();
}
