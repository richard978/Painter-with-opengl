#include "mainwindow.h"
#include "oglwidget.h"
#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle(QObject::tr("绘图编辑器 Early Access"));
    w.iniBtnColor();
    w.show();

    return a.exec();
}
