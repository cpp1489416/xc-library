#pragma once

#include "CXCGL.h"
#include <QDockWidget>
#include <QtWidgets>

class CameraSettingsDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit CameraSettingsDock(QWidget *parent);
    ~CameraSettingsDock();
    void SetCamera(Camera * camera) { mCamera = camera; }

signals:
    void ChangedSignal();

    private slots:
        void PithcButtonClicked();
        void YawButtonClicked();
        void RollButtonClicked();
        void ChangedSlot();

public:
    Camera * mCamera;
    QLineEdit *lineEdits[9];
};
