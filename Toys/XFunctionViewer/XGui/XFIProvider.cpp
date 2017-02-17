#include "XFIProvider.h"
#include "../XFunctionSolver2/XFunctionParser.h"
#include <qmessagebox.h>
#include <qpainter.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <qcoreapplication.h>
#include <qthread.h>

// sin(sin(x) + cos(y)) - cos(sin(x * y) + cos(x))
// sin(x ^ 2 + y ^ 2) - cos(x * y)
// exp(sin(x) + cos(y)) - sin(exp(x + y))
// x / sin(x) + y / sin(y) - x * y / sin(x * y)

XFIProvider::XFIProvider(QObject *parent)
{
    parser = new XFunctionParser;
    newton = new XNewton;
    limit = 20;

    source = "exp(sin(x) + cos(y)) - sin(exp(x + y))";

    image = new QImage;
}

XFIProvider::~XFIProvider()
{
    delete newton;
    delete parser;
    delete image;
}

void XFIProvider::genImage()
{
    delete image;
    image = new QImage(900, 900, QImage::Format::Format_RGBA8888);
    QPainter painter;
    painter.begin(image);

    painter.fillRect(0, 0, 900, 900, Qt::GlobalColor::white);

    painter.setPen(QPen(QColor(255, 0, 0)));
    for (int i = 0; i < arrayLen; i++)
    {
        for (int j = 0; j < arrayLen; j++)
        {
            if (mp[i][j])
            {
                painter.drawPoint(i, j);
            }
        }
    }

    painter.setPen(QPen(QColor(0, 0, 0)));
    painter.drawLine(0, 450, 900, 450);
    painter.drawLine(450, 0, 450, 900);
    painter.end();
}

XFunctionParser *XFIProvider::getParser() const
{
    return parser;
}

void XFIProvider::setSource(QString source)
{
    this->source = source.toStdString();
}

void XFIProvider::draw()
{
    genMp();
    genImage();
    emit createFinished();
}

XNewton *XFIProvider::getNewton() const
{
    return newton;
}

void XFIProvider::genMp()
{
    parser->setSource(source);
    newton->setFunction(parser);

    memset(mp, 0, sizeof(mp));

    unit = limit / (arrayLen / 2);

    int mi = arrayLen / 2 - limit / unit;
    int ma = arrayLen / 2 + limit / unit;

    newton->setVariable("x");

    for (int i = mi; i < ma; i++)
    {
        for (int j = mi; j < ma; j++)
        {
            double x = (i - arrayLen / 2) * unit;
            double y = (j - arrayLen / 2) * unit;

            if (fabs(newton->newton(x, y) - x) < unit / 2.0)
            {
                mp[i][j] = 1;
            }

        }

        if (i % 20 == 0)
        {
            float process = float(i * ma) / (ma * ma) / 2.0;
            emit processUpdated(process);
        }
    }

    newton->setVariable("y");
    for (int i = mi; i < ma; i++)
    {
        for (int j = mi; j < ma; j++)
        {
            double x = (i - arrayLen / 2) *   unit;
            double y = (j - arrayLen / 2) *    unit;

            if (fabs(newton->newton(x, y) - y) < unit / 2.0)
            {
                mp[i][j] = 1;
            }
        }

        if (i % 20 == 0)
        {
            float process = float(i * ma) / (ma * ma) / 2.0 + 0.5;
            emit processUpdated(process);
        }
    }
}

QImage *XFIProvider::getImage() const
{
    return image;
}