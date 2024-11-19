#include "tcpclientwidget.h"
#include "common.h"
#include "ui_tcpclientwidget.h"
#include <QFutureWatcher>
#include <QTcpSocket>
#include <QtConcurrent/QtConcurrent>

/**
 * @brief TCPClientWidget 构造函数
 *
 * 初始化 TCPClientWidget 对象，设置 UI 界面，并初始化网络相关资源。
 *
 * @param parent 父窗口指针
 */
TCPClientWidget::TCPClientWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TCPClientWidget) {
    ui->setupUi(this);
    ui->localIp->addItems(getIPAddresses());
    m_Socket = new QTcpSocket;
    connect(m_Socket, &QTcpSocket::disconnected, [=]() {
        ui->connect->setText("connect");
        appendLog(ui->textEdit, "disconnect");
    });
    connect(m_Socket, &QTcpSocket::readyRead, [=]() {
        QByteArray data = (ui->toHex->isChecked()) ? m_Socket->readAll().toHex()
                                                   : m_Socket->readAll();
        appendLog(ui->textEdit, QString(data));
    });
}

/**
 * @brief 析构函数
 *
 * 释放与界面相关的资源，并删除ui指针。
 */
TCPClientWidget::~TCPClientWidget() {
    delete ui;
}

/**
 * @brief 当点击连接按钮时触发的事件处理函数
 *
 * 根据当前按钮文本，判断是否进行连接或断开连接操作。
 * 如果当前按钮文本为"connect"，则尝试进行连接操作；
 * 如果当前按钮文本为"disconnect"，则尝试断开连接。
 */
void TCPClientWidget::on_connect_clicked() {
    if ("connect" == ui->connect->text()) {
        if (ui->bind->isChecked()) {
            if (!m_Socket->bind(QHostAddress(ui->localIp->currentText()),
                                ui->localPort->value())) {
                appendLog(ui->textEdit,
                          "bind error:" + m_Socket->errorString());
                return;
            }
        }
        ui->connect->setEnabled(false);
        m_Socket->connectToHost(QHostAddress(ui->serverIp->text()),
                                ui->serverPort->value());
        if (m_Socket->waitForConnected()) {
            ui->connect->setText("disconnect");

            appendLog(ui->textEdit, "connect");
        } else
            appendLog(ui->textEdit, "connect error:" + m_Socket->errorString());
        ui->connect->setEnabled(true);
    } else {
        m_Socket->close();
        m_Socket->disconnectFromHost();
        ui->connect->setText("connect");
        appendLog(ui->textEdit, "disconnect");
    }
}

/**
 * @brief 当点击发送按钮时触发的槽函数
 *
 * 根据用户是否在“转为十六进制”复选框中打勾，将文本框中的内容转换为十六进制或保持原样，
 * 然后通过已打开的套接字发送数据。
 */
void TCPClientWidget::on_send_clicked() {
    QByteArray data = (ui->toHex->isChecked())
        ? QByteArray::fromHex(ui->message->text().toUtf8())
        : ui->message->text().toUtf8();
    if (m_Socket->isOpen()) m_Socket->write(data, data.size());
}

/**
 * @brief 当点击“清除”按钮时调用
 *
 * 当用户在界面上点击“清除”按钮时，此函数会被调用。它会清除文本编辑框中的内容。
 */
void TCPClientWidget::on_clear_clicked() {
    ui->textEdit->clear();
}
