#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <XFIProvider.h>
#include <qlineedit.h>
#include "ximagewidget.h"
#include "xfpiprovider.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    public slots :
    void createButtonClicked();
    void genFPIButtonClicked();
    void createFIFinished();
    void processUpdated(float process);


signals:
    void operateFI();

private:

    XFIProvider *provider;
    QThread thread;
    XFPIProvider *FPIProvider;
    QLineEdit *lineEdit;
    XNewton *newton;
    QPushButton *createButton;
    XImageWidget *widget;
};

#endif // MAINWINDOW_H
