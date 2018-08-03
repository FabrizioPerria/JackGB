#include "glwindow.h"
#include <QString>
#include <QDebug>
#include <QtOpenGL>
#include "Rendering/Data/vertex.h"

static const Vertex vertices[] = {
  Vertex( QVector2D( 0.00f,  0.75f), QVector3D(1.0f, 0.0f, 0.0f) ),
  Vertex( QVector2D( 0.75f, -0.75f), QVector3D(0.0f, 1.0f, 0.0f) ),
  Vertex( QVector2D(-0.75f, -0.75f), QVector3D(0.0f, 0.0f, 1.0f) )
};


GLWindow::~GLWindow()
{
    makeCurrent();
    teardownGL();
}

void GLWindow::initializeGL()
{
    initializeOpenGLFunctions();
    makeCurrent();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //create GL program
    _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, "Rendering/Shaders/first.vert.glsl");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, "Rendering/Shaders/first.frag.glsl");
    _program->link();
    _program->bind();

    //create buffer to pass vertex data to VAO
    _vertex.create();
    _vertex.bind();
    _vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    _vertex.allocate(vertices, sizeof(vertices));

    //create VAO
    _VAO.create();
    _VAO.bind();
    _program->enableAttributeArray(0);
    _program->enableAttributeArray(1);
    _program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
    _program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

    //release objects
    _vertex.release();
    _VAO.release();
    _program->release();
}

void GLWindow::resizeGL(int width, int height)
{

}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    _program->bind();
    _VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / Vertex::stride());
    _VAO.release();
    _program->release();
}

void GLWindow::teardownGL()
{
    _vertex.destroy();
    _VAO.destroy();
    delete _program;
}

void GLWindow::printContextInformation()
{
    Q_ASSERT(context()->isValid());
    Q_ASSERT(!context()->isOpenGLES());

    qDebug() << "OpenGL Version: " << qPrintable(reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    qDebug() << "GLSL Version: "   << qPrintable(reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
  }
