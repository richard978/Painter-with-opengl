#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ColorDialog.h"
#include "oglwidget.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>

void MainWindow::iniBtnColor()
{
    ui->Dot->setStyleSheet("background-color: rgb(240,255,255)");
    ui->Line->setStyleSheet("background-color: rgb(240,255,255)");
    ui->Curve->setStyleSheet("background-color: rgb(240,255,255)");
    ui->emptyRect->setStyleSheet("background-color: rgb(240,255,255)");
    ui->Rectangle->setStyleSheet("background-color: rgb(240,255,255)");
    ui->Circle->setStyleSheet("background-color: rgb(240,255,255)");
    ui->filledCir->setStyleSheet("background-color: rgb(240,255,255)");
    ui->filedRR->setStyleSheet("background-color: rgb(240,255,255)");
    ui->RoundRect->setStyleSheet("background-color: rgb(240,255,255)");
    ui->rubber->setStyleSheet("background-color: rgb(240,255,255)");
    ui->dragSelect->setStyleSheet("color: white");
    ui->Width->setStyleSheet("color: white");
    ui->ColorEditor->setStyleSheet("color: white");

    ui->Dot->setDown(false);
    ui->Line->setDown(false);
    ui->Curve->setDown(false);
    ui->emptyRect->setDown(false);
    ui->Rectangle->setDown(false);
    ui->Circle->setDown(false);
    ui->filledCir->setDown(false);
    ui->filedRR->setDown(false);
    ui->RoundRect->setDown(false);
    ui->rubber->setDown(false);
    ui->dragSelect->setDown(false);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pColorDlg(NULL)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background-color: rgb(100,100,100)");
    tmpR = tmpG = tmpB = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showColorDlg()
{

    if(m_pColorDlg == NULL)
    {
        m_pColorDlg = new ColorDialog(this);
    }
    connect(m_pColorDlg, SIGNAL(sendEditedColor(QColor)), this, SLOT(getEditedColor(QColor)));
    m_pColorDlg->showDialog();
}

void MainWindow::getEditedColor(QColor color)
{
    tmpR = color.red()/255.0f;
    tmpG = color.green()/255.0f;
    tmpB = color.blue()/255.0f;
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
}

void MainWindow::fileSave()
{
    QFileDialog fileDialog(this);
    fileDialog.setWindowTitle(tr("保存"));
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter(tr("File (*.wbg)"));
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList fileNames;
    if(fileDialog.exec())
        fileNames = fileDialog.selectedFiles();

    if(fileNames.empty())
        return;

    QFile file(fileNames[0]);
    if(!file.open((QIODevice::WriteOnly | QIODevice::Text)))
        return;

    QTextStream out(&file);

    ui->openGLWidget->dotsOut(out);
    ui->openGLWidget->linesOut(out);
    ui->openGLWidget->rectsOut(out);
    ui->openGLWidget->roundRectsOut(out);
    ui->openGLWidget->curvesOut(out);
    ui->openGLWidget->circlesOut(out);
}

void MainWindow::fileOpen()
{
    QFileDialog fileDialog(this);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setNameFilter(tr("File (*.wbg)"));
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    QStringList fileNames;
    if(fileDialog.exec())
        fileNames = fileDialog.selectedFiles();

    if(fileNames.empty())
        return;

    QFile file(fileNames[0]);
    if(!file.open((QIODevice::ReadOnly | QIODevice::Text)))
        return;
    QTextStream in(&file);
    QMessageBox::StandardButton judge = ui->openGLWidget->clearScreen();
    if(judge == QMessageBox::Yes)
        ui->openGLWidget->fileIn(in);
}

void MainWindow::on_Dot_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->isRubber = 0;
    ui->openGLWidget->choosepattern(1);
    ui->Dot->setStyleSheet("background-color: rgb(0,191,255)");
    ui->Dot->setDown(true);
}

void MainWindow::on_Line_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(2);
    ui->Line->setStyleSheet("background-color: rgb(0,191,255)");
    ui->Line->setDown(true);
}

void MainWindow::on_Rectangle_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(3);
    ui->Rectangle->setStyleSheet("background-color: rgb(0,191,255)");
    ui->Rectangle->setDown(true);
}

void MainWindow::on_emptyRect_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(4);
    ui->emptyRect->setStyleSheet("background-color: rgb(0,191,255)");
    ui->emptyRect->setDown(true);
}

void MainWindow::on_Circle_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(5);
    ui->Circle->setStyleSheet("background-color: rgb(0,191,255)");
    ui->Circle->setDown(true);
}

void MainWindow::on_filledCir_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(6);
    ui->filledCir->setStyleSheet("background-color: rgb(0,191,255)");
    ui->filledCir->setDown(true);
}

void MainWindow::on_RoundRect_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(7);
    ui->RoundRect->setStyleSheet("background-color: rgb(0,191,255)");
    ui->RoundRect->setDown(true);
}

void MainWindow::on_filedRR_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(8);
    ui->filedRR->setStyleSheet("background-color: rgb(0,191,255)");
    ui->filedRR->setDown(true);
}

void MainWindow::on_rubber_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(1,1,1);
    ui->openGLWidget->isRubber = 1;
    ui->openGLWidget->choosepattern(1);
    ui->rubber->setStyleSheet("background-color: rgb(0,191,255)");
    ui->rubber->setDown(true);
}

void MainWindow::on_Curve_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(9);
    ui->Curve->setStyleSheet("background-color: rgb(0,191,255)");
    ui->Curve->setDown(true);
}

void MainWindow::on_dragSelect_clicked()
{
    iniBtnColor();
    ui->openGLWidget->chooseColor(tmpR, tmpG, tmpB);
    ui->openGLWidget->choosepattern(10);
    ui->dragSelect->setStyleSheet("background-color: rgb(0,191,255)");
    ui->dragSelect->setDown(true);
}


void MainWindow::on_action_Z_triggered()
{
    iniBtnColor();
    ui->openGLWidget->undo();
    ui->openGLWidget->update();
}

void MainWindow::on_ColorEditor_clicked()
{
    iniBtnColor();
    showColorDlg();
}

void MainWindow::on_actionSave_triggered()
{
    iniBtnColor();
    fileSave();
}

void MainWindow::on_actionOpen_triggered()
{
    iniBtnColor();
    fileOpen();
}

void MainWindow::on_action_R_triggered()
{
    iniBtnColor();
    ui->openGLWidget->redo();
    ui->openGLWidget->update();
}

void MainWindow::on_action_C_triggered()
{
    iniBtnColor();
    ui->openGLWidget->clearScreen();
}

void MainWindow::on_Width_currentIndexChanged(int index)
{
    ui->openGLWidget->chooseWidth(index);
}

