#ifndef XFIProvider_H
#define XFIProvider_H

#include <QtWidgets/QMainWindow>
#include <qimage.h>
#include <string>
#include "../XFunctionSolver2/XNewton.h"
#include <qpushbutton.h>
#include <qthread.h>
#include <qmessagebox.h>
//#pragma comment (lib, "XFunctionSolver2.lib")

class XFIProvider : public QObject
{
    Q_OBJECT

public:
    XFIProvider(QObject *parent = 0);
    ~XFIProvider();
    XNewton *getNewton() const;
    XFunctionParser *getParser() const;
    void setSource(QString source);
    QImage *getImage() const;

public slots:
    void  draw();

signals:
    void createFinished();
    void processUpdated(float process);

private:
    void genMp();
    void genImage();
    std::string source;
    XFunctionParser *parser;
    XNewton *newton;
    float limit;
    float unit;
    float centerX;
    float centerY;
    char mp[900][900];
    const int arrayLen = 900;
    QImage *image;
};

#endif // XFIProvider_H
