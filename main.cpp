#include "mainScene.h"
//#include "widget.h"
#include <QApplication>

//此窗口的逻辑编写已完成

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QVector<int>>("QVector<int>");
    Widget w;
    w.show();
    return a.exec();
}

