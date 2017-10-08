#ifndef XIMAGEWIDGET_H
#define XIMAGEWIDGET_H

#include <QWidget>

class XImageWidget : public QWidget
{
    Q_OBJECT

public:
    XImageWidget(QWidget *parent = 0);
    ~XImageWidget();
    void setImage(QImage *image);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QImage *image;
};

#endif // XIMAGEWIDGET_H
