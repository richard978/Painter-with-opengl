#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "ColorDialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void iniBtnColor();
    void showColorDlg();
    void fileSave();
    void fileOpen();

private slots:

    void getEditedColor(QColor color);

    void on_Dot_clicked();

    void on_Line_clicked();

    void on_Rectangle_clicked();

    void on_Circle_clicked();

    void on_RoundRect_clicked();

    void on_rubber_clicked();

    void on_emptyRect_clicked();

    void on_filledCir_clicked();

    void on_filedRR_clicked();

    void on_Curve_clicked();

    void on_action_Z_triggered();

    void on_ColorEditor_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_action_R_triggered();

    void on_action_C_triggered();

    void on_Width_currentIndexChanged(int index);

    void on_dragSelect_clicked();

private:
    Ui::MainWindow *ui;
    ColorDialog *m_pColorDlg;
    float tmpR, tmpG, tmpB;
};

#endif // MAINWINDOW_H
