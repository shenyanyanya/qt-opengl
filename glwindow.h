#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

class Tree {
    std::unique_ptr<QVector3D[]> treeTrunc;
    QVector3D treeTruncColor;
    std::vector<std::unique_ptr<QVector3D[]>> treeLeaves;
    QVector3D treeLeavesColor;
    int type;

public:
    Tree(int type, float width, float length, float height, float x, float y, float z);
    QVector3D* getTreeTrunc() const { return treeTrunc.get(); }
    QVector3D getTreeTruncColor() const { return treeTruncColor; }
    std::vector<std::unique_ptr<QVector3D[]>> const& getTreeLeaves() const { return treeLeaves; }
    QVector3D getTreeLeavesColor() const { return treeLeavesColor; }
};

class House {
    std::unique_ptr<QVector3D[]> houseBase;
    QVector3D houseBaseColor;
    std::vector<std::unique_ptr<QVector3D[]>> houseRoof;
    QVector3D houseRoofColor;
    int type;

public:
    House(int type, float width, float length, float height, float x, float y, float z);
    QVector3D* getHouseBase() const { return houseBase.get(); }
    QVector3D getHouseBaseColor() const { return houseBaseColor; }
    std::vector<std::unique_ptr<QVector3D[]>> const& getHouseRoof() const { return houseRoof; }
    QVector3D getHouseRoofColor() const { return houseRoofColor; }
};

class GLWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
    QPointF lastMousePosition;
    bool dragging;

    QMatrix4x4 rotateMatrix;
    float angle = 30.0;
    QMatrix4x4 modelViewMatrix;
    QMatrix4x4 projectMatrix;

    QOpenGLShaderProgram quadShaderProgram;

    const float platformW = 1000.0, platformL = platformW, platformH = 10.0;
    std::unique_ptr<QVector3D[]> platform;
    const float cellW = 50.0, cellL = 50.0;
    std::vector<std::pair<int, int>> freeCells;

    float zoffset = platformW / 8.0;

    std::vector<House> houses;
    std::vector<Tree> trees;

    void addTree();
    void addHouse();

    void freeAllCells();

    void resetProjection();
    void resetModelView();
    static void changeRotateMatrix(QMatrix4x4& rotate_matrix, float dx, float dy);

    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

    void initShader();

    void drawPlatform();
    void drawTrees();
    void drawHouses();

public:
    GLWindow();
    ~GLWindow();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
};
#endif // GLWINDOW_H
