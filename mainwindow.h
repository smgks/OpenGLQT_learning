#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>

struct vertData
{
    vertData() {}
    vertData(QVector3D p, QVector2D c, QVector3D n):pos(p),
    cords(c),normal(n)
    {

    }
    QVector3D pos;
    QVector2D cords;
    QVector3D normal;
};

class MainWindow : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initCube(float width);
private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_shProgram;
    QOpenGLTexture *m_texture;
    QOpenGLBuffer m_arrayBuffer;
    QOpenGLBuffer m_idexBuffer;
    QQuaternion m_quaterion;
};

#endif // MAINWINDOW_H
