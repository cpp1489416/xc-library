#ifndef XFPIPROVIDER_H
#define XFPIPROVIDER_H

#include <QObject>

#include "../XFunctionSolver2/XFunctionParser.h"

class QImage;
class QRectF;
class QPainter;

class XFPIProvider : public QObject
{
    Q_OBJECT

public:
    XFPIProvider(QObject *parent = 0);
    ~XFPIProvider();
    QImage *getImage() const;
    void setParser(XFunctionParser &parser);

    public slots:
    void draw();

private:
    void genImage(XAbstractParseNode *root, QRectF area);

    XAbstractParseNode *root;
    QImage *image;
    QPainter *painter;
    const int width = 1500;
    const int height = 900;
    const int uniteWidth = 50;
    bool visited[100][100];
};

#endif // XFPIPROVIDER_H
