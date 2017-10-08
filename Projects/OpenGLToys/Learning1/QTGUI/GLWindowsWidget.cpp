#include "GLWindowsWidget.h"
#include <GL/glew.h>
#include <QEvent>
#include <QResizeEvent>
#include <cassert>

GLWindowsWidget::GLWindowsWidget(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WidgetAttribute::WA_NativeWindow, true);

    InitializeWin32();
    glewInit();
}

GLWindowsWidget::~GLWindowsWidget()
{
}

void GLWindowsWidget::showEvent(QShowEvent * event)
{
    if (mInitialized == false)
    {
        mInitialized = true;
        OnInitializeOpenGL();
    }
}

void GLWindowsWidget::paintEvent(QPaintEvent * event)
{
    if (mInitialized)
    {
        OnPaintOpenGL();
        SwapBuffers(mHDC);
    }
}

void GLWindowsWidget::resizeEvent(QResizeEvent * event)
{
    if (mInitialized)
    {
        OnResizeOpenGL(event->size().width(), event->size().height());
    }
}

void GLWindowsWidget::InitializeWin32()
{
    mHWND = (HWND)winId();
    mHDC = GetDC(mHWND);

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        24, 8, 0,
        PFD_MAIN_PLANE, 0, 0, 0, 0
    };


    int windowPixelFormat = ChoosePixelFormat(mHDC, &pfd);
    SetPixelFormat(mHDC, windowPixelFormat, &pfd);

    mHGLRC = wglCreateContext(mHDC);
    if (FALSE == wglMakeCurrent(mHDC, mHGLRC))
    {
        assert(false);
    }
}

void GLWindowsWidget::OnInitializeOpenGL()
{
    // must override
}

void GLWindowsWidget::OnPaintOpenGL()
{
    // must override
}

void GLWindowsWidget::OnResizeOpenGL(int width, int height)
{
    // must override
}

