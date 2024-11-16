#include "udpwidget.h"
#include <QUdpSocket>
#include "common.h"
#include "ui_udpwidget.h"

/**
 * @brief UDPWidget 构造函数
 *
 * 初始化UDPWidget控件，设置UI，并创建UDP套接字。
 *
 * @param parent 父控件指针
 */
UDPWidget::UDPWidget(QWidget *parent) : QWidget(parent), ui(new Ui::UDPWidget) {
  ui->setupUi(this);
  ui->localIp_2->addItems(getIPAddresses());
  m_Socket = new QUdpSocket;
  connect(m_Socket, &QUdpSocket::readyRead, [=]() {
    while (m_Socket->hasPendingDatagrams()) {
      QByteArray data;
      QHostAddress host;
      quint16 port;
      data.resize(m_Socket->pendingDatagramSize());
      m_Socket->readDatagram(data.data(), data.size(), &host, &port);
      data = (ui->toHex_2->isChecked()) ? data.toHex() : data;
      appendLog(ui->textEdit, QString("%1:%2:%3")
                                  .arg(host.toString())
                                  .arg(port)
                                  .arg(QString(data)));
    }
  });
}

UDPWidget::~UDPWidget() { delete ui; }    // 释放用户界面资源

/**
 * @brief 绑定按钮点击事件处理函数
 *
 * 当用户点击绑定按钮时，此函数将被调用。根据按钮当前的文本状态，执行绑定或解绑操作。
 *
 * 如果按钮文本为"bind"，则尝试将套接字绑定到指定的本地IP地址和端口。
 * 如果绑定成功，将按钮文本更改为"unbind"；如果绑定失败，则在日志中添加错误信息。
 *
 * 如果按钮文本为"unbind"，则中止套接字连接，并将按钮文本恢复为"bind"。
 */
void UDPWidget::on_bind_clicked() {
  if (ui->bind->text() == "bind") {
    if (m_Socket->bind(QHostAddress(ui->localIp_2->currentText()),
                       ui->localPort_2->value()))
      ui->bind->setText("unbind");
    else
      appendLog(ui->textEdit, "bind error:" + m_Socket->errorString());
  } else {
    m_Socket->abort();
    ui->bind->setText("bind");
  }
}

/**
 * @brief 当点击发送按钮时调用的槽函数
 *
 * 该函数将用户输入的消息发送到指定的服务器。如果用户勾选了“转换为十六进制”选项，
 * 则将消息从文本转换为十六进制格式后再发送。
 *
 * @details 函数流程：
 * 1. 判断是否勾选了“转换为十六进制”选项。
 * 2. 如果是，将输入框中的文本转换为十六进制格式的QByteArray；
 *    否则，直接将输入框中的文本转换为UTF-8编码的QByteArray。
 * 3. 使用UDP套接字将转换后的数据发送到指定的服务器IP和端口。
 */
void UDPWidget::on_send_2_clicked() {
  QByteArray data = (ui->toHex_2->isChecked())
                        ? QByteArray::fromHex(ui->message_2->text().toUtf8())
                        : ui->message_2->text().toUtf8();
  m_Socket->writeDatagram(data, QHostAddress(ui->serverIp->text()),
                          ui->serverPort->value());
}

/**
 * @brief 清空文本编辑框中的内容
 * 
 * 当用户点击清除按钮时，该函数会被调用，以清空UI界面上标识为textEdit的文本编辑框中的所有内容。
 * 这使得用户能够方便地重置或清理文本编辑框，以便输入新的数据或开始新的操作。
 */
void UDPWidget::on_clear_2_clicked() { ui->textEdit->clear(); }
