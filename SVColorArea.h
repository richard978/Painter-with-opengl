#ifndef SVCOLORAREA_H
#define SVCOLORAREA_H

#include <QWidget>

class SVColorArea : public QWidget
{
    Q_OBJECT
public:
    SVColorArea(QWidget *parent);
    ~SVColorArea();

    void setHue(int);
    void setSaturation(int);
    void setBrightness(int);
    void setHsv(int, int, int);
    void setColor(const QColor &);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

private:
    void drawSVPixmap();
    void createVPixmap();
    void createSVPixmap();
    void updateSVPixmap();

public slots:
    void hueChangedSlot(int);

signals:
    void svChangedSignal(int, int, int);

private:
    int m_iHue;
    int m_iSaturation;
    int m_iBrightness;
    const int m_iAreaWidth;
    QPixmap m_svPixmap;
    QPixmap m_vPixmap;
};
#endif // SVCOLORAREA_H
