#include <qboxlayout.h>
#include <qmessagebox.h>
#include <qpalette.h>
#include <qpainter.h>
#include <qlabel.h>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    QHBoxLayout *layoutUp = new QHBoxLayout;
    lineEdit = new QLineEdit;
    layoutUp->addWidget(lineEdit);
    createButton = new QPushButton;
    createButton->setText("Generate Image");
    connect(createButton, SIGNAL(clicked(bool)), this, SLOT(createButtonClicked()));
    layoutUp->addWidget(createButton);

    QVBoxLayout *layoutRight = new QVBoxLayout;
    QPushButton *nbt = new QPushButton(QStringLiteral("查看语法树"));
    connect(nbt, &QPushButton::clicked, this, &MainWindow::genFPIButtonClicked);
    layoutRight->addWidget(nbt);
   // layoutRight->addWidget(new QLabel("ggre"));
    layoutRight->addStretch();

    QHBoxLayout *layoutDown = new QHBoxLayout;
    widget = new XImageWidget;
    layoutDown->addWidget(widget);
    layoutDown->addLayout(layoutRight);
    layoutDown->setStretchFactor(widget, 1);

    QVBoxLayout *layoutMain = new QVBoxLayout;
    layoutMain->addLayout(layoutUp);
    layoutMain->addLayout(layoutDown);

    setLayout(layoutMain);

    setGeometry(100, 100, 1000, 1000);


    provider = new XFIProvider;
    provider->moveToThread(&thread);
    connect(&thread, &QThread::finished, provider, &QObject::deleteLater);
    connect(this, &MainWindow::operateFI, provider, &XFIProvider::draw);
    connect(provider, &XFIProvider::createFinished, this, &MainWindow::createFIFinished);
    connect(provider, &XFIProvider::processUpdated, this, &MainWindow::processUpdated);

    FPIProvider = new XFPIProvider(this);
    thread.start();
}

MainWindow::~MainWindow()
{
    thread.quit();
    thread.wait();
}

void MainWindow::createButtonClicked()
{
    provider->setSource(lineEdit->text());
    emit operateFI();
}

void MainWindow::genFPIButtonClicked()
{
    FPIProvider->setParser(*provider->getParser());
    FPIProvider->draw();
    XImageWidget *widget = new XImageWidget;
    widget->setImage(FPIProvider->getImage());
    widget->show();
   
    // QMessageBox::information(this, "", "");
}

void MainWindow::createFIFinished()
{
    QImage *image = provider->getImage();
    widget->setImage(image);
 //.   QMessageBox::information(this, "", QString::fromStdString(provider->getParser()->getInfixExpression()));

}

void MainWindow::processUpdated(float process)
{
    setWindowTitle(QString::number(process));
}