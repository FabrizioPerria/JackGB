#include "mainwindow.h"
#include <QApplication>
#include "glwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(4,1);

    //MainWindow w;
    GLWindow w;
    w.setFormat(format);
    w.resize(QSize(800, 600));
    w.show();

    return a.exec();
}
