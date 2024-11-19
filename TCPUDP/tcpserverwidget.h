#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H
#include <QWidget>

// 定义数据包中各个字段的位置////////////////////
#define POS_HEADER0                   0
#define POS_HEADER1                   1
#define POS_DEV_ID                    2
#define POS_PKG_CNT                   3
#define POS_BATT_VOLT_H               4
#define POS_BATT_VOLT_L               5
///////////////////////////////////////////////

// 命名空间声明，包含界面元素
namespace Ui {
class TCPServerWidget;
}

// 声明QTcpServer和QTcpSocket类的使用
class QTcpServer;
class QTcpSocket;

/**
 * @brief The TCPServerWidget class represents a widget for TCP server functionality.
 * It inherits from QWidget and provides a graphical interface for users to interact with the TCP server.
 */
class TCPServerWidget : public QWidget {
    Q_OBJECT
public:
    // 构造函数，初始化TCPServerWidget
    explicit TCPServerWidget(QWidget *parent = nullptr);
    // 析构函数，释放TCPServerWidget资源
    ~TCPServerWidget();

private:
    // 获取指定行的socket对象
    QTcpSocket *socket(int row);

private slots:
    // 当用户点击"监听"按钮时触发
    void on_listen_clicked();
    // 当用户点击"关闭"按钮时触发
    void on_close_clicked();
    // 当用户点击"发送"按钮时触发
    void on_send_clicked();
    // 当用户点击"清除"按钮时触发
    void on_clear_clicked();
    // 当用户点击"打开LED0"按钮时触发
    void on_btn_OPEN_LED0_clicked();

private:
    // 用于操作界面元素的指针
    Ui::TCPServerWidget *ui;
    // 用于创建TCP服务器的指针
    QTcpServer *m_Server;
    // 存储客户端连接的列表
    QList<QTcpSocket *> m_Clients;
    // 计算CRC16校验和的函数
    quint16 crc16_ibm(QByteArray crcdata, quint16 length);
    // 打印数据包内容的函数
    void PrintState(QByteArray package);
};
#endif // TCPSERVERWIDGET_H