#ifndef TCPCLIENTWIDGET_H
#define TCPCLIENTWIDGET_H

#include <QWidget>

// 声明一个UI类，用于界面展示
namespace Ui {
class TCPClientWidget;
}

// QTcpSocket类用于实现TCP套接字功能
class QTcpSocket;

// TCPClientWidget类继承自QWidget，用于创建TCP客户端界面
class TCPClientWidget : public QWidget {
    Q_OBJECT

public:
    // 构造函数，初始化TCP客户端界面
    explicit TCPClientWidget(QWidget *parent = nullptr);
    // 析构函数，释放TCP客户端界面资源
    ~TCPClientWidget();

private slots:
    // 当点击连接按钮时触发，用于建立TCP连接
    void on_connect_clicked();

    // 当点击发送按钮时触发，用于发送数据
    void on_send_clicked();

    // 当点击清除按钮时触发，用于清除界面显示内容
    void on_clear_clicked();

private:
    // ui用于管理界面元素
    Ui::TCPClientWidget *ui;
    // m_Socket用于TCP通信
    QTcpSocket *m_Socket;
};

#endif // TCPCLIENTWIDGET_H