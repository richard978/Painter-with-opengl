#ifndef HCOLORAREA_H
#define HCOLORAREA_H

#include <QWidget>

class HColorArea : public QWidget
{
    Q_OBJECT

public:
    HColorArea(QWidget *parent);
    ~HColorArea();
    void setHue(int);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    void createHuePixmap();

signals:
    void hueChangedSignal(int);

private:
    QPixmap m_huePixmap;
    double m_hue;
    int m_iHue;
    const int m_iColorHeight;
    const int m_iColorWidth;
    const int topMargin = 7;
    const int rightMargn = 9;
};

#endif // HCOLORAREA_H
