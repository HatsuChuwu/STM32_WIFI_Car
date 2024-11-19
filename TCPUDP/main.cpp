#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // 创建一个QApplication对象
    QApplication a(argc, argv);

    // 创建一个MainWindow对象
    MainWindow w;

    // 显示MainWindow窗口
    w.show();

    // 进入QApplication的事件循环
    return a.exec();
}

