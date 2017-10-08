#include "MainWindow.h"
#include "MatrixViewDock.h"
#include <qdockwidget.h>
#include <qlayout.h>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowState(Qt::WindowState::WindowMaximized);
    mHouseWidget = new GLHouseWidget;
    setCentralWidget(mHouseWidget);
    mCameraDock = new CameraSettingsDock(0);
    addDockWidget(Qt::RightDockWidgetArea, mCameraDock);
    mCameraDock->SetCamera(&mHouseWidget->mCamera);
    connect(mCameraDock, &CameraSettingsDock::ChangedSignal, this, &MainWindow::ButtonClicked);
    
    MatrixViewDock *matrixViewDock = new MatrixViewDock(nullptr);
    addDockWidget(Qt::RightDockWidgetArea, matrixViewDock);
    tabifyDockWidget(mCameraDock, matrixViewDock);

//    matrixViewDock->AddMatrix(&mHouseWidget->mCamera.GetMatrix(), "Camera Matrix");
    matrixViewDock->AddMatrix(&mHouseWidget->mCamera.mProjectionMatrix, "Projection Matrix");
}

MainWindow::~MainWindow()
{
}

void MainWindow::ButtonClicked()
{
    // QMessageBox::information(this, "", "");

    mHouseWidget->update();
}
