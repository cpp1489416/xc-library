#ifndef GLWindowsWidget_H
#define GLWindowsWidget_H

#include <QWidget>
#include <QTimer>
#include <Windows.h>
#include "CXCGL.h"

class GLWindowsWidget : public QWidget
{
    Q_OBJECT

public:
    GLWindowsWidget(QWidget * parent = 0);
    ~GLWindowsWidget();
    
public:
    QPaintEngine * paintEngine() const override final { return nullptr; }

public:
    HWND GetHWND() const { return mHWND; }
    HDC GetHDC() const { return mHDC; }
    HGLRC GetHGLRC() const { return mHGLRC; }

protected:
    void showEvent(QShowEvent * event) override final;
    void paintEvent(QPaintEvent * event) override final;
    void resizeEvent(QResizeEvent * event) override final;

protected:
    virtual void OnInitializeOpenGL();
    virtual void OnPaintOpenGL();
    virtual void OnResizeOpenGL(int width, int height);

private:
    void InitializeWin32();

private:
    bool mInitialized = false;
    HWND mHWND;
    HDC mHDC;
    HGLRC mHGLRC;
};

#endif // GLWindowsWidget_H    