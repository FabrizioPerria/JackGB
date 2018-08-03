#include "display.h"
#include <QSurfaceFormat>

Display::Display()
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,1);

    _window = new GLWindow();
    _window->setFormat(format);
    _window->resize(QSize(800, 600));
    _window->show();
}

void Display::Reset()
{
}

void Display::Render()
{

}
