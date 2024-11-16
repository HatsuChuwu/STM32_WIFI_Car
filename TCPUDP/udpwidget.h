#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include <QWidget>

// 声明一个UI命名空间，用于封装UI相关类
namespace Ui {
class UDPWidget;
}

// 声明一个QUdpSocket类，用于UDP网络通信
class QUdpSocket;

// 定义一个UDPWidget类，继承自QWidget，用于创建UDP通信的图形界面窗口
class UDPWidget : public QWidget {
  Q_OBJECT

 public:
  // 构造函数，初始化UDPWidget对象，可以接受一个父窗口指针作为参数
  explicit UDPWidget(QWidget *parent = nullptr);
  // 析构函数，用于释放UDPWidget对象
  ~UDPWidget();

 private slots:
  // 当绑定按钮被点击时调用的槽函数，用于处理绑定操作
  void on_bind_clicked();

  // 当发送按钮被点击时调用的槽函数，用于处理发送操作
  void on_send_2_clicked();

  // 当清空按钮被点击时调用的槽函数，用于处理清空操作
  void on_clear_2_clicked();

 private:
  // 定义一个Ui::UDPWidget指针，用于访问UI元素
  Ui::UDPWidget *ui;
  // 定义一个QUdpSocket指针，用于UDP网络通信
  QUdpSocket *m_Socket;
};

#endif  // UDPWIDGET_H