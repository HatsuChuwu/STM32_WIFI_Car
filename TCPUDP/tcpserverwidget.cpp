#include "tcpserverwidget.h"
#include "common.h"
#include "ui_tcpserverwidget.h"
#include <QHeaderView>
#include <QTcpServer>
#include <QTcpSocket>
/**
 * @brief TCPServerWidget 类的构造函数
 * @param parent 父控件指针
 */
TCPServerWidget::TCPServerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TCPServerWidget) {
    ui->setupUi(this);
    ui->localIp->addItem("Any");
    ui->localIp->addItems(getIPAddresses());
    ui->clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);
    m_Server = new QTcpServer;
    ///////当有新的连接请求时，接受连接并处理客户端的通信//////////////////////////////
    connect(m_Server, &QTcpServer::newConnection, [=]() {
        QTcpSocket *tcpSocket = m_Server->nextPendingConnection();
        QString ip = tcpSocket->peerAddress().toString();
        quint16 port = tcpSocket->peerPort();
        appendLog(ui->textEdit, QString("%1:%2:connect").arg(ip).arg(port));
        bool r = false;
        for (int i = 0; i < ui->clientTable->rowCount(); ++i) {
            QTableWidgetItem *ipitem = ui->clientTable->item(i, 0);
            QTableWidgetItem *portitem = ui->clientTable->item(i, 1);
            if (nullptr != ipitem && nullptr != portitem &&
                ipitem->text() == ip && portitem->text().toUShort() == port) {
                r = true;
                break;
            }
        }
        ///////////////////////////////////////////////////////////////////////
        ////// 当客户端断开连接时，更新日志并从客户端列表中移除该客户端////////////////
        connect(tcpSocket, &QTcpSocket::disconnected, [=]() {
            appendLog(ui->textEdit,
                      QString("%1:%2 disconnected")
                          .arg(tcpSocket->peerAddress().toString())
                          .arg(tcpSocket->peerPort()));
            for (int i = 0; i < ui->clientTable->rowCount(); ++i) {
                QTableWidgetItem *ipitem = ui->clientTable->item(i, 0);
                QTableWidgetItem *portitem = ui->clientTable->item(i, 1);
                if (nullptr != ipitem && nullptr != portitem &&
                    ipitem->text() == ip &&
                    portitem->text().toUShort() == port) {
                    ui->clientTable->removeRow(i);
                    break;
                }
            }
            for (QTcpSocket *socket : m_Clients) {
                if (ip == socket->peerAddress().toString() &&
                    port == socket->peerPort()) {
                    m_Clients.removeOne(socket);
                    socket = nullptr;
                    break;
                }
            }
        });
        ///////////////////////////////////////////////////////////
        //当客户端有数据可读时，读取数据并根据设置进行处理（如转换为十六进制）
        //然后将数据显示在日志中/////////////////////////////////////
        connect(tcpSocket, &QTcpSocket::readyRead, [=]()
        {
            QByteArray data = tcpSocket->readAll();
            PrintState(data);
            if(ui->toHex->isChecked())
            {
                data = data.toHex();
            }
            appendLog(ui->textEdit,
                      QString("%1:%2:%3").arg(ip).arg(port).arg(QString(data)));
        });
        /*connect(tcpSocket, &QTcpSocket::readyRead, [=]()
        {
            QByteArray data = (ui->toHex->isChecked())
                ? tcpSocket->readAll().toHex()
                : tcpSocket->readAll();
            appendLog(ui->textEdit,
                      QString("%1:%2:%3").arg(ip).arg(port).arg(QString(data)));
             PrintState(data);
        });*/
        ////////////将新连接的客户端添加到客户端列表中////////////////
        m_Clients.append(tcpSocket);
        //////在客户端表格中插入新行，显示客户端的 IP 地址和端口号//////
        int row = ui->clientTable->rowCount();
        ui->clientTable->insertRow(row);
        ui->clientTable->setItem(row, 0, new QTableWidgetItem(ip));
        ui->clientTable->setItem(row, 1,
                                 new QTableWidgetItem(QString::number(port)));

    });
}
/**
 * @brief TCPServerWidget 类的析构函数
 */
TCPServerWidget::~TCPServerWidget() {
    delete ui;
}
/**
 * @brief 根据行号获取客户端的 QTcpSocket 指针
 * @param row 行号
 * @return 指向客户端 QTcpSocket 的指针，如果未找到则返回 nullptr
 */
QTcpSocket *TCPServerWidget::socket(int row) {
    QTableWidgetItem *ipitem = ui->clientTable->item(row, 0);
    QTableWidgetItem *portitem = ui->clientTable->item(row, 1);
    if (nullptr != ipitem && nullptr != portitem) {
        QString ip = ipitem->text();
        quint16 port = portitem->text().toUShort();
        for (QTcpSocket *tcpSocket : m_Clients) {
            if (ip == tcpSocket->peerAddress().toString() &&
                port == tcpSocket->peerPort())
                return tcpSocket;
        }
    }
    return nullptr;
}
/**
 * @brief 处理监听按钮的点击事件
 * 如果按钮文本为 "listen"，则尝试开始监听指定的 IP 地址和端口号
 * 如果按钮文本为 "listening"，则停止监听并重置按钮文本为 "listen"
 */
void TCPServerWidget::on_listen_clicked() {

    if (ui->listen->text() == "listen") {
        if (m_Server->listen((ui->localIp->currentText() == "Any")
                                 ? QHostAddress::Any
                                 : QHostAddress(ui->localIp->currentText()),
                             ui->localPort->value())) {
            ui->listen->setText("listening");
            appendLog(ui->textEdit, "start listening");
        } else {
            appendLog(ui->textEdit,
                      "start listen error:" + m_Server->errorString());
        }
    } else {
        m_Server->close();
        ui->listen->setText("listen");
        for (QTcpSocket *tcpSocket : m_Clients) {
            tcpSocket->close();
            tcpSocket->disconnectFromHost();
        }
        m_Clients.clear();
        appendLog(ui->textEdit, "stop listening");
    }
}
/**
 * @brief 处理关闭按钮的点击事件
 * 关闭当前选中的客户端连接，并从客户端表格中移除该客户端
 */
void TCPServerWidget::on_close_clicked() {
    int row = ui->clientTable->currentRow();
    QTcpSocket *tcpSocket = socket(row);
    if (nullptr != tcpSocket) {
        tcpSocket->close();
        tcpSocket->disconnectFromHost();
    }
}
/**
 * @brief 处理发送按钮的点击事件
 * 将用户输入的消息（文本或十六进制）发送给当前选中的客户端
 */
void TCPServerWidget::on_send_clicked() {
    QByteArray data = (ui->toHex->isChecked())
        ? QByteArray::fromHex(ui->message->text().toUtf8())
        : ui->message->text().toUtf8();
    int row = ui->clientTable->currentRow();
    QTcpSocket *tcpSocket = socket(row);
    if (nullptr != tcpSocket)tcpSocket->write(data, data.size());
}
/**
 * @brief 处理清除按钮的点击事件
 * 清除日志文本框中的内容
 */
void TCPServerWidget::on_clear_clicked() {
    ui->textEdit->clear();
}
/**
 * @brief 打印状态信息
 * @param package 数据包
 */
void TCPServerWidget::PrintState(QByteArray package)
{
    char *buf = package.data();
    int len = package.size();
    unsigned int data;
    float float_data;
    QString rbytes;
    qint16 Rcrc;
    ///检查数据包的前两个字节是否为 0xAA 和 0xCC///
    if(((unsigned char)buf[0]!=0xAA)||((unsigned char)buf[1]!=0xCC))
    {
        return;
    }
    Rcrc=crc16_ibm(package, len-2);//计算数据包的CRC校验值
    //检查 CRC 校验值是否正确
    if(((package.at(len-2)&0xff)!=((Rcrc>>8)&0xff)) || ((package.at(len-1)&0xff)!=(Rcrc&0xff)))//CRC校验错误
    {
        return;
    }

    //设备ID
    data = ((unsigned char)buf[POS_DEV_ID])&0xff;//从数据包位置（POS_DEV_ID）读取一个字节的数据，并将其转换为无符号整数
    rbytes=rbytes.asprintf("%d",data);//使用asprintf函数将设备ID格式化为字符串
    switch(data){
    case 1:
        ui->label_DEV_ID->setText(rbytes);
        break;
    case 2:
        ui->label_DEV_ID_2->setText(rbytes);
        break;
    case 3:
        ui->label_DEV_ID_3->setText(rbytes);
        break;
    default:
        break;
    }

    //包计数器
    //从数据包的指定位置（POS_PKG_CNT）读取一个字节的数据，并将其显示在标签上
    data = ((unsigned char)buf[POS_PKG_CNT]) & 0xff;
    rbytes = rbytes.asprintf("%d", data);
    switch (data) {
    case 1:
        ui->label_PACKET_CNT->setText(rbytes);
        break;
    case 2:
        ui->label_PACKET_CNT_2->setText(rbytes);
        break;
    case 3:
        ui->label_PACKET_CNT_3->setText(rbytes);
        break;
    default:
        break;
    }

    //电池电压
    /**在这段代码中，高字节乘以256是因为在处理16位数据时，通常将数据分为高字节和低字节两部分。
     * 每个字节有8位，所以16位数据需要两个字节来表示
     * 当从数据包中读取电池电压的高字节和低字节时，我们需要将它们组合成一个16位的值。为了实现这一点，我们将高字节左移8位（即乘以256，因为2^8 = 256），然后加上低字节
     * 在二进制表示中，左移8位相当于在数值的左侧添加8个0，这为低字节腾出了空间，使得我们可以将两个字节的值合并成一个16位的值
     * 低字节不需要乘以256，因为它已经是数据的最低有效位，直接加上高字节左移后的值就可以得到完整的16位数据
     * 总结一下，高字节乘以256是为了将其放置在16位数据的高8位位置，而低字节保持不变，直接放在低8位位置，这样就可以正确地组合成一个16位的值
     */
    data = ((unsigned char)buf[POS_BATT_VOLT_H]*256)+(unsigned char)buf[POS_BATT_VOLT_L];//通过将高字节乘以256并加上低字节，可以得到一个16位的值，代表电池电压原始测量值
    float_data = (float)(3.3*2*data/4096);//将原始测量值转换为实际的电压值，3.3是参考电压，2是因为使用了分压电路（5V电池，2个10k分压），4096是ADC的分辨率
    rbytes=rbytes.asprintf("%5.3f",float_data);//使用asprintf函数将电池电压格式化为字符串，保留3位小数
    switch (data) {
    case 1:
        ui->label_BATT_VOLT->setText(rbytes);
        break;
    case 2:
        ui->label_BATT_VOLT_2->setText(rbytes);
        break;
    case 3:
        ui->label_BATT_VOLT_3->setText(rbytes);
        break;
    default:
        break;
    }
}
/**
 * @brief 计算 CRC16-IBM 校验值
 * @param crcdata 数据
 * @param length 数据长度
 * @return CRC 校验值
 */
quint16 TCPServerWidget::crc16_ibm(QByteArray crcdata, quint16 length)
{
    quint8 i,data;
    quint16 j=0;
    quint16 crc = 0;        // 初始值
    while(length--)
    {
        data=crcdata.at(j++);
        crc ^= data;        // crc ^= *data; data++;
        for (i = 0; i < 8; ++i)
        {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xA001;        // 0xA001 = reverse 0x8005
            else
                crc = (crc >> 1);
        }
    }
    return crc;
}
/**
 * @brief 处理打开或关闭 LED0 的按钮点击事件
 */
// 定义一个名为 on_btn_OPEN_LED0_clicked 的槽函数，当按钮被点击时触发
void TCPServerWidget::on_btn_OPEN_LED0_clicked()
{
    QByteArray sendStr;
    quint16 tcrc;
    sendStr.append(24,char(0x0)); //创建一个字节数组 sendStr，初始大小为 24，填充字符 0x0
    sendStr[0]=0xAA;
    sendStr[1]=0xCC;
    sendStr[2]=0x01;//设备ID DEV_ID
    sendStr[3]=0x01;//命令ID CMD_ID
    if(ui->btn_OPEN_LED0->text()=="打开")
    {
        sendStr[4]=0x01;
        ui->btn_OPEN_LED0->setText("关闭");
        ui->btn_OPEN_LED0->setStyleSheet(QString("background-color:") + "green");
    }else if(ui->btn_OPEN_LED0->text()=="关闭")
    {
        sendStr[4]=0x00;
        ui->btn_OPEN_LED0->setText("打开");
        ui->btn_OPEN_LED0->setStyleSheet(QString("background-color:") + "white");
    }else
    {
        return;
    }
    tcrc=crc16_ibm(sendStr, 22);// 计算 sendStr 数组前 22 个字节的 CRC16 校验值
    sendStr[22]=uchar(tcrc>>8);//将计算得到的 CRC 校验值的高 8 位存入 sendStr 数组的第 22 个字节
    sendStr[23]=uchar(tcrc);// 将计算得到的 CRC 校验值的低 8 位存入 sendStr 数组的第 23 个字节

    int row = ui->clientTable->currentRow();//获取当前选中的行号
    QTcpSocket *tcpSocket = socket(row);//根据行号获取对应的 QTcpSocket 对象
    if (nullptr != tcpSocket)tcpSocket->write(sendStr);//如果 tcpSocket 对象不为空，则向其写入 sendStr 数据
    //将 sendStr 数据写入串口 serial.write(sendStr);
}
