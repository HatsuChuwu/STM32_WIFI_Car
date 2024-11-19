#ifndef COMMON_H
#define COMMON_H
#include <QDateTime>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QTextEdit>
static QStringList getIPAddresses() {
    QStringList addresses; // 初始化地址列表

    // 遍历网络接口的所有地址
    for (const QHostAddress &address : QNetworkInterface::allAddresses()) {
        // 检查地址是否为IPv4协议
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
            // 将IPv4地址添加到地址列表中
            addresses.append(address.toString());
    }

    return addresses; // 返回地址列表
}

static QString currentTimeStr() {
    // 获取当前日期和时间
    return QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss.zzz");
    // 将当前日期和时间转换为字符串并返回
}

static void appendLog(QTextEdit *logEdit, const QString &log) {
    // 将当前时间和日志信息拼接成一个字符串
    // "%1" 和 "%2" 是占位符，分别被 currentTimeStr() 和 log 替换
    logEdit->append(QString("%1:%2").arg(currentTimeStr()).arg(log));
    // 调用 QTextEdit 的 append 方法将拼接后的字符串添加到文本编辑框中
}

#endif // COMMON_H
