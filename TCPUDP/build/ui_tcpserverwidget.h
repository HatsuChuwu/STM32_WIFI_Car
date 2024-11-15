/********************************************************************************
** Form generated from reading UI file 'tcpserverwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCPSERVERWIDGET_H
#define UI_TCPSERVERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCPServerWidget
{
public:
    QCheckBox *toHex;
    QComboBox *localIp;
    QSpinBox *localPort;
    QPushButton *listen;
    QPushButton *close;
    QLineEdit *message;
    QPushButton *send;
    QTextEdit *textEdit;
    QTableWidget *clientTable;
    QPushButton *clear;
    QFrame *line;
    QFrame *line_2;
    QLabel *label;
    QFrame *line_3;
    QLabel *label_2;
    QLabel *label_3;
    QFrame *line_4;
    QLabel *label_4;
    QLabel *label_PACKET_CNT;
    QLabel *label_5;
    QLabel *label_DEV_ID;
    QLabel *label_6;
    QLabel *label_BATT_VOLT;
    QPushButton *btn_OPEN_LED0;
    QLabel *label_7;
    QLabel *label_DEV_ID_2;
    QLabel *label_BATT_VOLT_2;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_PACKET_CNT_2;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_BATT_VOLT_3;
    QLabel *label_DEV_ID_3;
    QLabel *label_13;
    QLabel *label_PACKET_CNT_3;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QFrame *line_5;
    QFrame *line_6;
    QFrame *line_7;

    void setupUi(QWidget *TCPServerWidget)
    {
        if (TCPServerWidget->objectName().isEmpty())
            TCPServerWidget->setObjectName("TCPServerWidget");
        TCPServerWidget->resize(900, 600);
        toHex = new QCheckBox(TCPServerWidget);
        toHex->setObjectName("toHex");
        toHex->setGeometry(QRect(360, 110, 51, 30));
        localIp = new QComboBox(TCPServerWidget);
        localIp->setObjectName("localIp");
        localIp->setGeometry(QRect(10, 10, 161, 30));
        localIp->setMinimumSize(QSize(120, 0));
        localPort = new QSpinBox(TCPServerWidget);
        localPort->setObjectName("localPort");
        localPort->setGeometry(QRect(180, 10, 72, 30));
        localPort->setMinimum(1);
        localPort->setMaximum(65535);
        localPort->setValue(5555);
        listen = new QPushButton(TCPServerWidget);
        listen->setObjectName("listen");
        listen->setGeometry(QRect(270, 10, 93, 30));
        close = new QPushButton(TCPServerWidget);
        close->setObjectName("close");
        close->setGeometry(QRect(390, 10, 93, 30));
        message = new QLineEdit(TCPServerWidget);
        message->setObjectName("message");
        message->setGeometry(QRect(10, 60, 351, 30));
        send = new QPushButton(TCPServerWidget);
        send->setObjectName("send");
        send->setGeometry(QRect(390, 60, 93, 30));
        textEdit = new QTextEdit(TCPServerWidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(280, 150, 331, 431));
        textEdit->setReadOnly(true);
        textEdit->setTabStopDistance(80.000000000000000);
        clientTable = new QTableWidget(TCPServerWidget);
        if (clientTable->columnCount() < 2)
            clientTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        clientTable->setObjectName("clientTable");
        clientTable->setGeometry(QRect(10, 150, 250, 431));
        clientTable->setMaximumSize(QSize(250, 16777215));
        clientTable->setGridStyle(Qt::PenStyle::SolidLine);
        clear = new QPushButton(TCPServerWidget);
        clear->setObjectName("clear");
        clear->setGeometry(QRect(520, 110, 93, 30));
        line = new QFrame(TCPServerWidget);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 40, 631, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(TCPServerWidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 100, 631, 16));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        label = new QLabel(TCPServerWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 120, 131, 16));
        line_3 = new QFrame(TCPServerWidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(260, 110, 20, 491));
        line_3->setFrameShape(QFrame::Shape::VLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        label_2 = new QLabel(TCPServerWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(280, 110, 91, 30));
        label_3 = new QLabel(TCPServerWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(450, 110, 91, 30));
        line_4 = new QFrame(TCPServerWidget);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(620, 0, 20, 601));
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        label_4 = new QLabel(TCPServerWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(650, 60, 101, 30));
        label_PACKET_CNT = new QLabel(TCPServerWidget);
        label_PACKET_CNT->setObjectName("label_PACKET_CNT");
        label_PACKET_CNT->setGeometry(QRect(760, 60, 72, 30));
        label_PACKET_CNT->setFrameShape(QFrame::Shape::StyledPanel);
        label_5 = new QLabel(TCPServerWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(650, 30, 101, 30));
        label_DEV_ID = new QLabel(TCPServerWidget);
        label_DEV_ID->setObjectName("label_DEV_ID");
        label_DEV_ID->setGeometry(QRect(760, 30, 72, 30));
        label_DEV_ID->setFrameShape(QFrame::Shape::StyledPanel);
        label_6 = new QLabel(TCPServerWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(650, 90, 101, 30));
        label_BATT_VOLT = new QLabel(TCPServerWidget);
        label_BATT_VOLT->setObjectName("label_BATT_VOLT");
        label_BATT_VOLT->setGeometry(QRect(760, 90, 72, 30));
        label_BATT_VOLT->setFrameShape(QFrame::Shape::StyledPanel);
        btn_OPEN_LED0 = new QPushButton(TCPServerWidget);
        btn_OPEN_LED0->setObjectName("btn_OPEN_LED0");
        btn_OPEN_LED0->setGeometry(QRect(760, 400, 93, 30));
        label_7 = new QLabel(TCPServerWidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(650, 400, 101, 30));
        label_DEV_ID_2 = new QLabel(TCPServerWidget);
        label_DEV_ID_2->setObjectName("label_DEV_ID_2");
        label_DEV_ID_2->setGeometry(QRect(760, 150, 72, 30));
        label_DEV_ID_2->setFrameShape(QFrame::Shape::StyledPanel);
        label_DEV_ID_2->setFrameShadow(QFrame::Shadow::Plain);
        label_BATT_VOLT_2 = new QLabel(TCPServerWidget);
        label_BATT_VOLT_2->setObjectName("label_BATT_VOLT_2");
        label_BATT_VOLT_2->setGeometry(QRect(760, 210, 72, 30));
        label_BATT_VOLT_2->setFrameShape(QFrame::Shape::StyledPanel);
        label_8 = new QLabel(TCPServerWidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(650, 210, 101, 30));
        label_9 = new QLabel(TCPServerWidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(650, 150, 101, 30));
        label_10 = new QLabel(TCPServerWidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(650, 180, 101, 30));
        label_PACKET_CNT_2 = new QLabel(TCPServerWidget);
        label_PACKET_CNT_2->setObjectName("label_PACKET_CNT_2");
        label_PACKET_CNT_2->setGeometry(QRect(760, 180, 72, 30));
        label_PACKET_CNT_2->setFrameShape(QFrame::Shape::StyledPanel);
        label_PACKET_CNT_2->setFrameShadow(QFrame::Shadow::Plain);
        label_11 = new QLabel(TCPServerWidget);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(650, 300, 101, 30));
        label_12 = new QLabel(TCPServerWidget);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(650, 330, 101, 30));
        label_BATT_VOLT_3 = new QLabel(TCPServerWidget);
        label_BATT_VOLT_3->setObjectName("label_BATT_VOLT_3");
        label_BATT_VOLT_3->setGeometry(QRect(760, 330, 72, 30));
        label_BATT_VOLT_3->setFrameShape(QFrame::Shape::StyledPanel);
        label_DEV_ID_3 = new QLabel(TCPServerWidget);
        label_DEV_ID_3->setObjectName("label_DEV_ID_3");
        label_DEV_ID_3->setGeometry(QRect(760, 270, 72, 30));
        label_DEV_ID_3->setFrameShape(QFrame::Shape::StyledPanel);
        label_13 = new QLabel(TCPServerWidget);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(650, 270, 101, 30));
        label_PACKET_CNT_3 = new QLabel(TCPServerWidget);
        label_PACKET_CNT_3->setObjectName("label_PACKET_CNT_3");
        label_PACKET_CNT_3->setGeometry(QRect(760, 300, 72, 30));
        label_PACKET_CNT_3->setFrameShape(QFrame::Shape::StyledPanel);
        label_14 = new QLabel(TCPServerWidget);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(650, 10, 41, 21));
        label_15 = new QLabel(TCPServerWidget);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(650, 130, 41, 21));
        label_16 = new QLabel(TCPServerWidget);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(650, 250, 41, 21));
        line_5 = new QFrame(TCPServerWidget);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(630, 120, 631, 16));
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);
        line_6 = new QFrame(TCPServerWidget);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(630, 240, 631, 16));
        line_6->setFrameShape(QFrame::Shape::HLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);
        line_7 = new QFrame(TCPServerWidget);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(630, 360, 631, 16));
        line_7->setFrameShape(QFrame::Shape::HLine);
        line_7->setFrameShadow(QFrame::Shadow::Sunken);

        retranslateUi(TCPServerWidget);

        QMetaObject::connectSlotsByName(TCPServerWidget);
    } // setupUi

    void retranslateUi(QWidget *TCPServerWidget)
    {
        TCPServerWidget->setWindowTitle(QCoreApplication::translate("TCPServerWidget", "Form", nullptr));
        toHex->setText(QCoreApplication::translate("TCPServerWidget", "hex", nullptr));
        listen->setText(QCoreApplication::translate("TCPServerWidget", "listen", nullptr));
        close->setText(QCoreApplication::translate("TCPServerWidget", "close", nullptr));
        send->setText(QCoreApplication::translate("TCPServerWidget", "send", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("TCPServerWidget", "ip", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("TCPServerWidget", "port", nullptr));
        clear->setText(QCoreApplication::translate("TCPServerWidget", "clear", nullptr));
        label->setText(QCoreApplication::translate("TCPServerWidget", "\345\256\242\346\210\267\347\253\257\344\277\241\346\201\257\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("TCPServerWidget", "\345\215\201\345\205\255\350\277\233\345\210\266\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("TCPServerWidget", "\346\270\205\351\231\244\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("TCPServerWidget", "\346\225\260\346\215\256\345\214\205\347\274\226\345\217\267\357\274\232", nullptr));
        label_PACKET_CNT->setText(QString());
        label_5->setText(QCoreApplication::translate("TCPServerWidget", "\350\256\276\345\244\207ID\345\217\267\357\274\232", nullptr));
        label_DEV_ID->setText(QString());
        label_6->setText(QCoreApplication::translate("TCPServerWidget", "\347\224\265\346\261\240\347\224\265\345\216\213\345\200\274\357\274\232", nullptr));
        label_BATT_VOLT->setText(QString());
        btn_OPEN_LED0->setText(QCoreApplication::translate("TCPServerWidget", "\346\211\223\345\274\200", nullptr));
        label_7->setText(QCoreApplication::translate("TCPServerWidget", "LED\346\216\247\345\210\266\357\274\232", nullptr));
        label_DEV_ID_2->setText(QString());
        label_BATT_VOLT_2->setText(QString());
        label_8->setText(QCoreApplication::translate("TCPServerWidget", "\347\224\265\346\261\240\347\224\265\345\216\213\345\200\274\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("TCPServerWidget", "\350\256\276\345\244\207ID\345\217\267\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("TCPServerWidget", "\346\225\260\346\215\256\345\214\205\347\274\226\345\217\267\357\274\232", nullptr));
        label_PACKET_CNT_2->setText(QString());
        label_11->setText(QCoreApplication::translate("TCPServerWidget", "\346\225\260\346\215\256\345\214\205\347\274\226\345\217\267\357\274\232", nullptr));
        label_12->setText(QCoreApplication::translate("TCPServerWidget", "\347\224\265\346\261\240\347\224\265\345\216\213\345\200\274\357\274\232", nullptr));
        label_BATT_VOLT_3->setText(QString());
        label_DEV_ID_3->setText(QString());
        label_13->setText(QCoreApplication::translate("TCPServerWidget", "\350\256\276\345\244\207ID\345\217\267\357\274\232", nullptr));
        label_PACKET_CNT_3->setText(QString());
        label_14->setText(QCoreApplication::translate("TCPServerWidget", "\345\260\217\350\275\2461", nullptr));
        label_15->setText(QCoreApplication::translate("TCPServerWidget", "\345\260\217\350\275\2462", nullptr));
        label_16->setText(QCoreApplication::translate("TCPServerWidget", "\345\260\217\350\275\2463", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TCPServerWidget: public Ui_TCPServerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCPSERVERWIDGET_H
