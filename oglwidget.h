#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QTextStream>
#include <QMessageBox>

class OGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    friend class MainWindow;
public:
    OGLWidget(QWidget *parent = 0);
    ~OGLWidget();
    bool isRubber;
    void _init();
    void choosepattern(int id);
    void chooseColor(float R, float G, float B);
    void chooseWidth(int index);
    void undo();
    void redo();
    QMessageBox::StandardButton clearScreen();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    float Pi=3.1415926536f;

    bool activeDot;
    bool activeLine;
    bool activeCurve;
    bool activeRect;
    bool activeCircle;
    bool activeRoundRect;
    bool activeDrag;
    bool filled;
    bool release;
    float lineWidth;
    float mouseMoveTempX, mouseMoveTempY;

    QList<int> patternPainted;
    QList<int> patternPaintedR;

    struct color{
        float R,G,B;
    };
    color curColor;
    void printList();

    //Draw Dots
    float dotx, doty;
    struct dots{
        float dotx, doty, size;
        color c;
    };
    QList<dots> Dlist;
    QList<dots> Dlisttmp;
    void printDot();

    //Draw Lines
    int lineReleased;
    float lineX1, lineX2, lineX3;
    float lineY1, lineY2, lineY3;
    struct lines{
        float x1, x2, y1, y2;
        int released;
        color c;
        float w;
    };
    QList<lines> Llist;
    QList<lines> Llisttmp;
    void printLines();

    //Draw Curves
    QList<QPair<float,float> > coor;
    struct curves{
        float x1, x2, x3, x4;
        float y1, y2, y3, y4;
        color c;
        float w;
    };
    QList<curves> Curlist;
    QList<curves> Curlisttmp;
    void printCurves();

    //Draw Rectangles
    int rectReleased;
    float RectX1, RectX2, RectX3;
    float RectY1, RectY2, RectY3;
    struct Rects{
        float x1, x2, y1, y2;
        int released;
        color c;
        bool filled;
        float w;
    };
    QList<Rects> Rlist;
    QList<Rects> Rlisttmp;
    void printRects();

    //Draw RoundRect
    int roundRectReleased;
    float RRectX1, RRectX2, RRectX3;
    float RRectY1, RRectY2, RRectY3;
    struct RoundRect{
        float x, y, w, h;
        int released;
        color c;
        bool filled;
        float wid;
    };
    QList<RoundRect> RRlist;
    QList<RoundRect> RRlisttmp;
    void printRoundRect();

    //Draw CirCles
    int cirReleased;
    float CirX1, CirX2, CirX3;
    float CirY1, CirY2, CirY3;
    struct Circles{
        float x1, x2, y1, y2;
        int released;
        color c;
        bool filled;
        float w;
    };
    QList<Circles> Clist;
    QList<Circles> Clisttmp;
    void printCirs();

    //Drag
    float DragX, DragY;
    int selectedPattern, selectedIndex;

public:
    void dotsOut(QTextStream &out);
    void linesOut(QTextStream &out);
    void rectsOut(QTextStream &out);
    void roundRectsOut(QTextStream &out);
    void curvesOut(QTextStream &out);
    void circlesOut(QTextStream &out);

    void fileIn(QTextStream &in);
};

#endif // OGLWIDGET_H
