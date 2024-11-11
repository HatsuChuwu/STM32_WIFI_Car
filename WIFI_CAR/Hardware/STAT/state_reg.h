#ifndef __STATE_REG_H
#define __STATE_REG_H	 
#include "stm32f1xx_hal.h"
//////////////////////////////////////////////////////////////////////////////////	 						  
extern uint8_t STAT_BUF[64];//�������мĴ���
//extern uint32_t PACKET_CNT;
#define  STAT_PACKET_LENGTH      30            //��������ͷ2�ֽڣ����ǰ���У����
#define  DEVICE_ID               1
////////////////////////////////////////////////////////////////////////////////// 
//���¶�����״̬�б������״̬��
#define  HEADER0           STAT_BUF[0] //0xAA
#define  HEADER1           STAT_BUF[1] //0xCC
#define  DEV_ID            STAT_BUF[2] 
#define  PKG_CNT           STAT_BUF[3] 
#define  BATT_VOLT_H       STAT_BUF[4] 
#define  BATT_VOLT_L       STAT_BUF[5] 
#define  PKG_RSV2          STAT_BUF[6] 
#define  PKG_RSV3          STAT_BUF[7] 
#define  PKG_RSV4          STAT_BUF[8] 
#define  PKG_RSV5          STAT_BUF[9] 
#define  PKG_RSV6          STAT_BUF[10] 
#define  PKG_RSV7          STAT_BUF[11] 
#define  PKG_RSV8          STAT_BUF[12] 
#define  PKG_RSV9          STAT_BUF[13] 
#define  PKG_RSV10         STAT_BUF[14] 
#define  PKG_RSV11         STAT_BUF[15] 
#define  PKG_RSV12         STAT_BUF[16] 
#define  PKG_RSV13         STAT_BUF[17] 
#define  PKG_RSV14         STAT_BUF[18] 
#define  PKG_RSV15         STAT_BUF[19] 
#define  PKG_RSV16         STAT_BUF[20] 
#define  PKG_RSV17         STAT_BUF[21] 
#define  PKG_RSV18         STAT_BUF[22] 
#define  PKG_RSV19         STAT_BUF[23] 
#define  PKG_RSV20         STAT_BUF[24] 
#define  PKG_RSV21         STAT_BUF[25] 
#define  PKG_RSV22         STAT_BUF[26] 
#define  PKG_RSV23         STAT_BUF[27] 
#define  PKG_RSV24         STAT_BUF[28] 
#define  PKG_RSV25         STAT_BUF[29] 
//#define  PKG_RSV26         STAT_BUF[30] 
//#define  PKG_RSV27         STAT_BUF[31] 

/////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////// 
//���¶���������������
#define  CMD_OPEN_LED0                        0x01
//#define  CMD_QUERY_VERSION                     0x02
//#define  CMD_QUERY_STAT                        0x03

//////////////////////////////////////////////////////////////////////////////////
void UART2_COMMAND_PROCESSING(void);
/////////////////////////////////////

#endif




















