#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) { // MainWindow类的构造函数
  ui->setupUi(this); // 初始化UI界面

  // 设置窗口标题
  setWindowTitle("智能小车监控软件");

  // 设置窗口大小
  resize(900,680);
}

MainWindow::~MainWindow() { delete ui; }
