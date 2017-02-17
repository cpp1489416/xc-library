#include "CameraSettingsDock.h"

#include <QtWidgets>

CameraSettingsDock::CameraSettingsDock(QWidget *parent)
    : QDockWidget(parent)
{
    setWindowTitle("Camera");
    QWidget *mainWidget = new QWidget;
    setWidget(mainWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainWidget->setLayout(mainLayout);

    for (int i = 0; i < 9; i++)
    {
        QLineEdit * &cur = lineEdits[i];
        cur = new QLineEdit;
    }

    mainLayout->addWidget(new QLabel("Eye Position:"));
    for (int i = 0; i < 3; i++)
    {

        mainLayout->addWidget(lineEdits[i]); 
    }

    mainLayout->addWidget(new QLabel("Target Position:"));
    for (int i = 3; i < 6; i++) { mainLayout->addWidget(lineEdits[i]); }
    mainLayout->addWidget(new QLabel("Up Vector:"));
    for (int i = 6; i < 9; i++) { mainLayout->addWidget(lineEdits[i]); }
    QPushButton *setButton = new QPushButton("Set");
    connect(setButton, &QPushButton::clicked, this, &CameraSettingsDock::ChangedSlot);
    mainLayout->addWidget(setButton);

    QPushButton *pitchButton = new QPushButton("Pitch");
    mainLayout->addWidget(pitchButton);
    connect(pitchButton, &QPushButton::clicked, this, &CameraSettingsDock::PithcButtonClicked);

    QPushButton * yawButton = new QPushButton("Yaw");
    mainLayout->addWidget(yawButton);
    connect(yawButton, &QPushButton::clicked, this, &CameraSettingsDock::YawButtonClicked);

    QPushButton * rollButton = new QPushButton("Roll");
    mainLayout->addWidget(rollButton);
    connect(rollButton, &QPushButton::clicked, this, &CameraSettingsDock::RollButtonClicked);

    mainLayout->addStretch();

}

CameraSettingsDock::~CameraSettingsDock()
{

}

void CameraSettingsDock::ChangedSlot()
{
    mCamera->LookAt(
        lineEdits[0]->text().toFloat(), lineEdits[1]->text().toFloat(), lineEdits[2]->text().toFloat(),
        lineEdits[3]->text().toFloat(), lineEdits[4]->text().toFloat(), lineEdits[5]->text().toFloat(),
        lineEdits[6]->text().toFloat(), lineEdits[7]->text().toFloat(), lineEdits[8]->text().toFloat()
    );
    
    emit ChangedSignal();
}

void CameraSettingsDock::PithcButtonClicked()
{
    mCamera->Pitch(1);
    emit ChangedSignal();
}

void CameraSettingsDock::YawButtonClicked()
{
    mCamera->Yaw(1);
    emit ChangedSignal();
}

void CameraSettingsDock::RollButtonClicked()
{
    mCamera->Roll(1);
    emit ChangedSignal();
}