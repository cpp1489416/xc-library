#include "MainWindow.h"
#include <qdockwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qevent.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setGeometry(100, 100, 500, 500);
    widget = new DWidget;
    setCentralWidget(widget);
    QDockWidget *dock = new QDockWidget;
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dock);
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *rotateX = new QPushButton("Rotate X");
    connect(rotateX, &QPushButton::clicked, widget, &DWidget::rotateX);
    layout->addWidget(rotateX);

    QPushButton *rotateY = new QPushButton("Rotate Y");
    connect(rotateY, &QPushButton::clicked, widget, &DWidget::rotateY);
    layout->addWidget(rotateY);

    QPushButton *rotateZ = new QPushButton("Rotate Z");
    connect(rotateZ, &QPushButton::clicked, widget, &DWidget::rotateZ);
    layout->addWidget(rotateZ);

    QTimer *timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &MainWindow::timeout);
    timer->start(1);
    timer->stop();

    QPushButton *startButton = new QPushButton("Start");
    connect(startButton, SIGNAL(clicked()), timer, SLOT(start()));
    layout->addWidget(startButton);

    QPushButton *pauseButton = new QPushButton("Pause");
    connect(pauseButton, &QPushButton::clicked, timer, &QTimer::stop);
    layout->addWidget(pauseButton);

    layout->addStretch();

    QWidget *dockInWidget = new QWidget;
    dockInWidget->setLayout(layout);
    dock->setWidget(dockInWidget);

    setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

MainWindow::~MainWindow()
{

}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    DCamera *camera = widget->getCamera();

    switch (event->key())
    {
    case Qt::Key_W:
    {
        camera->walk(0.1f);
        widget->update();
       // QMessageBox::information(this, "hrthiegrug", "ghouer9");
        break;
    }
    case Qt::Key_S:
    {
        camera->walk(-0.1f);
        widget->update();
        break;
    }
    case Qt::Key_A:
    {
        camera->strafe(-0.1f);
        widget->update();
        break;
    }
    case Qt::Key_D:
    {
        camera->strafe(0.1f);
        widget->update();
        break;
    }
    case Qt::Key_Z:
    {
        camera->yaw(0.1f);
        widget->update();
        break;
    }
    case Qt::Key_X:
    {
        camera->pitch(0.01f);
        widget->update();
        break;
    }
    case Qt::Key_C:
    {
        camera->roll(0.01f);
        widget->update();
        break;
    }
    case Qt::Key_Up:
    {
        camera->fly(0.1f);
        widget->update();
        break;
    }
    case Qt::Key_Down:
    {
        camera->fly(-0.1f);
        widget->update();
        break;
    }
    default:
        break;
    }
}

void MainWindow::timeout()
{
    widget->getCamera()->yaw(0.1f);;
    widget->update();
}