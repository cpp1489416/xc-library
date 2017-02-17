#pragma once

#include <QMainWindow>
#include "GLHouseWidget.h"   
#include "CameraSettingsDock.h"

class MainWindow : public QMainWindow
{
        Q_OBJECT

public:
    MainWindow(QWidget *parent);
    ~MainWindow();

    private slots:
    void ButtonClicked();

private:
    GLHouseWidget * mHouseWidget;
    CameraSettingsDock * mCameraDock;
};
