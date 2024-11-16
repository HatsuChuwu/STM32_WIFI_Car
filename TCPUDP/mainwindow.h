#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// 主窗口类，继承自QMainWindow
class MainWindow : public QMainWindow
{
    // Q_OBJECT宏是Qt的元对象编译器使用的，用于提供内省和信号槽机制
    Q_OBJECT

public:
    // 构造函数，初始化主窗口
    // 参数parent是一个指向父窗口的指针，用于支持Qt的父子关系模型
    MainWindow(QWidget *parent = nullptr);
    
    // 析构函数，释放主窗口占用的资源
    ~MainWindow();

private:
    // 声明一个指向Ui::MainWindow的指针，用于管理窗口的UI元素
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H