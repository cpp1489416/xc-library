#pragma once

#include "GLWindowsWidget.h"
#include "../CXCGL.h"
#include "../ShaderPrograms/BasicShaderProgram.h"
#include "../ShaderPrograms/LightingShaderProgram.h"
#include "../ShaderPrograms/TextureShaderProgram.h"
#include "../ShaderPrograms/TextureLightingShaderProgram.h"
#include "../ShaderPrograms/ShadowShaderProgram.h"
#include "../Things/Circle.h"
#include "../Things/Anchor.h"
#include "../Things/TriangularPyramid.h"
#include "../Things/Cube.h"
#include "../Things/Sphere.h"
#include "../Things/Quad.h"

class GLHouseWidget final : public GLWindowsWidget
{
    Q_OBJECT

public:
    explicit GLHouseWidget(QWidget *parent = 0);
    ~GLHouseWidget() {}

public:
    void DropLightCamera(float value);

protected:
    void OnInitializeOpenGL() override final;
    void OnPaintOpenGL() override final;
    void OnResizeOpenGL(int width, int height) override final;
    void mousePressEvent(QMouseEvent * event) override final;
    void mouseMoveEvent(QMouseEvent * event) override final;
    void keyPressEvent(QKeyEvent *event) override final;

public:
    BasicShaderProgram mBasicShaderProgram;
    LightingShaderProgram mLightingShaderProgram;
    TextureShaderProgram mTextureShaderProgram;
    TextureLightingShaderProgram mTextureLightingShaderProgram;
    ShadowShaderProgram mShadowShaderProgram;
    
    PointLight mPointLight;
    Camera mCamera;
    Camera mLightCamera;
    
    Skybox mSkybox;
    Anchor mAnchor;
    Cube mLightPositionCube;
    Cube mCube;
    Cube mCube2;
    Sphere mSphere;
    Sphere mTextureSphere;
    Quad mQuadBottom;
    Quad mQuadBack;
    Quad mQuadLeft;

private:
    void UpdateScene();

private:
    QPointF mLastPosition;
    QTimer * mTimer;
};
