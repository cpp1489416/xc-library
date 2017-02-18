#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public: public slots :
    void timeout();


protected:
    virtual void keyPressEvent(QKeyEvent *event);

private:
    DWidget *widget;
};

#endif // MAINWINDOW_H
