#pragma once

#include <QMainWindow>
#include "MainWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

public slots:
    void AddClicked();
    void EraseRandomClicked();
    void EraseClicked();

private:
    MainWidget * mMainWidget;
};
