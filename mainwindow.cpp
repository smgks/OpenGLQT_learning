#include "mainwindow.h"
#include <QApplication>
#include <QOpenGLShader>

MainWindow::MainWindow(QWidget *parent) :
    QOpenGLWidget(parent),m_texture(nullptr),
    m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
    m_idexBuffer(QOpenGLBuffer::IndexBuffer)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST); // буфер глубины

    glEnable(GL_CULL_FACE); //отсечений задней грани для оптимизации

    initShaders();
    initCube(3.0f);
}

void MainWindow::resizeGL(int w, int h)
{
    float aspect = w / qreal(h ? h : 1);
    m_projectionMatrix.setToIdentity(); //к единичной матрице
    m_projectionMatrix.perspective(65,aspect,0.1f,10.0f);// формируем матрицу перспективы для отображения

}

void MainWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelVeivMatrix;
    modelVeivMatrix.setToIdentity();
    modelVeivMatrix.translate(0.0,0.0,-5.0);
    modelVeivMatrix.rotate(30,30,30,30);
    m_texture->bind(0);

    m_shProgram.setUniformValue("qt_ModelViewProjectionMatrix",m_projectionMatrix * modelVeivMatrix);
    m_shProgram.setUniformValue("qt_Texture0",0);

    m_arrayBuffer.bind();
    m_idexBuffer.bind();

    int offset = 0;

    int verLoc = m_shProgram.attributeLocation("qt_Vertex");
    m_shProgram.enableAttributeArray(verLoc);
    m_shProgram.setAttributeBuffer(verLoc,GL_FLOAT,offset,3,sizeof(vertData));

    offset +=sizeof(QVector3D);
    int texLoc = m_shProgram.attributeLocation("qt_MultiTexCoord0");
    m_shProgram.enableAttributeArray(texLoc);
    m_shProgram.setAttributeBuffer(texLoc,GL_FLOAT,offset,2,sizeof(vertData));

    glDrawElements(GL_TRIANGLES,m_idexBuffer.size(),GL_UNSIGNED_INT,0);
}

void MainWindow::initShaders()
{
    if(!m_shProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vshader.vsh"))
        close();
    if(!m_shProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fshader.fsh"))
        close();
    if(!m_shProgram.bind())
        close();
    if(!m_shProgram.link())
        close();
}

void MainWindow::initCube(float width)
{
    float width_div_2 = width / 2;
    QVector<vertData> vertexes;

    //front, right, top, back, left, down

    // Top side
    vertexes.append(vertData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f)));


    // Down side
    vertexes.append(vertData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0f, -1.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f, 0.0f), QVector3D(0.0f, -1.0f, 0.0f)));

    // Left side

    vertexes.append(vertData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(-1.0f, 0.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f, 0.0f), QVector3D(-1.0f, 0.0f, 0.0f)));

    // Right side
    vertexes.append(vertData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(1.0f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f, 0.0f), QVector3D(1.0f, 0.0f, 0.0f)));

    // Front side
    vertexes.append(vertData(QVector3D(-width_div_2, width_div_2, width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, -width_div_2, width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, width_div_2, width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, -width_div_2, width_div_2), QVector2D(1.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f)));

    // Back side
    vertexes.append(vertData(QVector3D(width_div_2, width_div_2, -width_div_2), QVector2D(0.0f, 1.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(vertData(QVector3D(width_div_2, -width_div_2, -width_div_2), QVector2D(0.0f, 0.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, width_div_2, -width_div_2), QVector2D(1.0f, 1.0f), QVector3D(0.0f, 0.0f, -1.0f)));
    vertexes.append(vertData(QVector3D(-width_div_2, -width_div_2, -width_div_2), QVector2D(1.0f, 0.0f), QVector3D(0.0f, 0.0f, -1.0f)));

    QVector<GLuint> indexes;
    for (int i = 0; i < 24; i+=4) {
        indexes.append(i + 0);
        indexes.append(i + 1);
        indexes.append(i + 2);
        indexes.append(i + 2);
        indexes.append(i + 1);
        indexes.append(i + 3);
    }

m_arrayBuffer.create();
m_arrayBuffer.bind();
m_arrayBuffer.allocate(vertexes.constData(),vertexes.size() * sizeof(vertData));
m_arrayBuffer.release();

m_idexBuffer.create();
m_idexBuffer.bind();
m_idexBuffer.allocate(indexes.constData(),indexes.size() * sizeof(GLuint));
m_idexBuffer.release();

m_texture = new QOpenGLTexture(QImage(":/iashchyk2.jpg").mirrored());
m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
m_texture->setWrapMode(QOpenGLTexture::Repeat);
}

