#include "ImageFileLoader.h"
#include <QImage>
#include <QPainter>
#include <QOpenGLWidget>
#include <QGLWidget>

class ImageFileLoader::IMPL
{
public:
    QImage mImage;
    QImage mGLImage;
};

ImageFileLoader::ImageFileLoader() :
    mIMPL(new IMPL)
{
}

ImageFileLoader::~ImageFileLoader()
{
    delete mIMPL;
}

void ImageFileLoader::Create(const char * path)
{
    mIMPL->mImage = QImage(path);
    
    QImage fixedImage = QImage(mIMPL->mImage.width(), mIMPL->mImage.height(), QImage::Format_ARGB32);
    QPainter painter(&fixedImage);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, mIMPL->mImage);
    painter.end();

    mIMPL->mGLImage = QGLWidget::convertToGLFormat(fixedImage);
}

void * ImageFileLoader::GetData()
{
    return mIMPL->mGLImage.bits();
}

GLsizei ImageFileLoader::GetWidth()
{
    return mIMPL->mGLImage.width();
}

GLsizei ImageFileLoader::GetHeight()
{
    return mIMPL->mGLImage.height();
}

GLenum ImageFileLoader::GetFormat()
{
    return GL_RGBA;
}

GLenum ImageFileLoader::GetDataType()
{
    return GL_UNSIGNED_BYTE;
}
