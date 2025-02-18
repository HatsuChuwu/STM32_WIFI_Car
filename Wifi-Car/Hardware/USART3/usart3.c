/*
 * FILE                : usart.c
 * DESCRIPTION         : This file is iCore3 usart driver demo.
 * Author              : zh.
 * Copyright           :
 *
 * History
 * --------------------
 * Rev                 : 0.00
 * Date                : 07/11/2019
 *
 * create.
 * --------------------
 */

//------------------------ Include files ------------------------//

#include "usart1.h"
#include "usart2.h"
#include "usart3.h"
#include "usart.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "CRC16.h" 
#include "atk_mw8266d.h"
//--------------------- Function Prototype ----------------------//

static int send_string_to_usart3(char * str);
static int initialize_usart3(unsigned long int baudrate);
static int my_printf3(const char * fmt,...);

//--------------------------- Variable --------------------------// 

USART3_T usart3 = {
	.USART_RX_STA = 0,
	.receive_ok_flag = 0,
	.counter = 0,
	.send_string = send_string_to_usart3,
	.initialize = initialize_usart3,
	.printf = my_printf3
};

extern UART_HandleTypeDef huart3;

//--------------------------- Function --------------------------//
/*
 * Name               : initialize_usart2
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *
 * create.
 * -------------------
 */
static int initialize_usart3(unsigned long int baudrate)
{
  huart3.Init.BaudRate = baudrate;
	if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    while(1);
  }	
	HAL_UART_Receive_IT(&huart3, (unsigned char *)&usart3.receive_data,1);
	
	return 0;
}

/*
 * Name               : send_string_to_usart2
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *
 * create.
 * -------------------
 */
static int send_string_to_usart3(char * str)
{
	while(*str != '\0'){
		while(!(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == 1));
		HAL_UART_Transmit(&huart3,(unsigned char*)str++,1,1000);
	}
	while(!(__HAL_UART_GET_FLAG(&huart3,UART_FLAG_TC) == 1));
	
	return 0;
}
/*
 * Name               : HAL_UART_RxCpltCallback
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *
 * create.
 * -------------------
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t Res;
	uint16_t Rcrc;
	if(huart == &huart3){
		HAL_UART_IRQHandler(&huart3);

		while(HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart3,(unsigned char *)&usart3.receive_data,1) != HAL_OK);
		
		Res = usart3.receive_data;//��ȡ���յ�������
		if((usart3.USART_RX_STA&0x8000)==0)//����δ��ɲŻ����������̣������������ˣ���Ҫ�ȴ����������꽫��־�������ܼ������ա�
		{
			if((usart3.USART_RX_STA&0x4000)==0)//��û���յ���0xAA
			{
				if(Res==0xAA) 
				{
					usart3.receive_buffer[usart3.USART_RX_STA&0X1FFF]=Res ;
				  usart3.USART_RX_STA++;
					usart3.USART_RX_STA|=0x4000;	//bit14��־λ��1
				}
				else return;//û���յ�0xAA�������������Ҳ����0xAA�����˳�
			}
			else if((usart3.USART_RX_STA&0x2000)==0)//�Ѿ��յ�0XAA,��û���յ���0xCC
			{
				if(Res==0xCC)//�յ�0xCC
				{	
					usart3.receive_buffer[usart3.USART_RX_STA&0X1FFF]=Res ;
				  usart3.USART_RX_STA++;
					usart3.USART_RX_STA|=0x2000;	//bit13��־λ��1
				}
				else usart3.USART_RX_STA=0;//���մ���,���¿�ʼ
			}
			else//�����ǽ��հ�ͷ��������ݰ�
			{
				usart3.receive_buffer[usart3.USART_RX_STA&0X1FFF]=Res ;
				usart3.USART_RX_STA++;
				if((usart3.USART_RX_STA&0x1fff)==24)//����24�ֽ�
				{
					if(1)//1--CRCУ��; 0--����ҪУ��
					{
						Rcrc=crc16_ibm((uint8_t*)usart3.receive_buffer,22);//����CRCУ��ֵ
						if(((Rcrc&0xff)==usart3.receive_buffer[23]) && (((Rcrc>>8)&0xff)==usart3.receive_buffer[22]))
						{
							usart3.USART_RX_STA|=0x8000;	//��������� 
						}else
						{
							usart3.USART_RX_STA=0;//���մ���,���¿�ʼ
						}
					}else{
						usart3.USART_RX_STA|=0x8000;	//��������� 
					}
				}
			}
		}
	}else if(huart == &huart1){
		HAL_UART_IRQHandler(&huart1);

		while(HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart1,(unsigned char *)&usart1.receive_data,1) != HAL_OK);
		
		Res = usart1.receive_data;//��ȡ���յ�������
		//usart6.printf("%x,",Res);
		if((usart1.USART_RX_STA&0x8000)==0)//����δ��ɲŻ����������̣������������ˣ���Ҫ�ȴ����������꽫��־�������ܼ������ա�
		{
			if((usart1.USART_RX_STA&0x4000)==0)//��û���յ���0xAA
			{
				if(Res==0xAA) 
				{
					//usart2.printf("receive a AA\r\n");
					usart1.receive_buffer[usart1.USART_RX_STA&0X1FFF]=Res ;
				  usart1.USART_RX_STA++;
					usart1.USART_RX_STA|=0x4000;	//bit14��־λ��1
				}
				else return;//û���յ�0xAA�������������Ҳ����0xAA�����˳�
			}
			else if((usart1.USART_RX_STA&0x2000)==0)//�Ѿ��յ�0XAA,��û���յ���0xCC
			{
				if(Res==0xCC)//�յ�0xCC
				{	
					//usart2.printf("receive CC\r\n");
					usart1.receive_buffer[usart1.USART_RX_STA&0X1FFF]=Res ;
				  usart1.USART_RX_STA++;
					usart1.USART_RX_STA|=0x2000;	//bit13��־λ��1
				}
				else usart1.USART_RX_STA=0;//���մ���,���¿�ʼ
			}
			else//�����ǽ��հ�ͷ��������ݰ�
			{
				usart1.receive_buffer[usart1.USART_RX_STA&0X1FFF]=Res ;
				usart1.USART_RX_STA++;
				if((usart1.USART_RX_STA&0x1fff)==24)//����24�ֽ�
				{
					//usart2.printf("receive a packet\r\n");
					//printf("�յ����ݰ���\r\n");
					//usart6.send_packet((unsigned char*)usart1.receive_buffer, 24);
					Rcrc=crc16_ibm((uint8_t*)usart1.receive_buffer,22);//����CRCУ��ֵ
					if(((Rcrc&0xff)==usart1.receive_buffer[23]) && (((Rcrc>>8)&0xff)==usart1.receive_buffer[22]))
					{
						usart1.USART_RX_STA|=0x8000;	//��������� 
						//usart2.printf("CRCУ��ɹ�%x\r\n", Rcrc);
						//printf("CRCУ��ɹ�%x\r\n", Rcrc);
					}else
					{
						usart1.USART_RX_STA=0;//���մ���,���¿�ʼ
						//usart2.printf("CRCУ�����%x\r\n", Rcrc);
						//printf("CRCУ�����%x\r\n", Rcrc);
					}
				}
			}
		} 
	}else if(huart == &huart2){
		HAL_UART_IRQHandler(&huart2);
		if (__HAL_UART_GET_FLAG(&huart2, UART_FLAG_ORE) != RESET)        /* UART���չ��ش����ж� */
    {
        __HAL_UART_CLEAR_OREFLAG(&huart2);                           /* ������չ��ش����жϱ�־ */
        (void)huart2.Instance->SR;                                   /* �ȶ�SR�Ĵ������ٶ�DR�Ĵ��� */
        (void)huart2.Instance->DR;
    }
		while(HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY);
		while(HAL_UART_Receive_IT	(&huart2,(unsigned char *)&usart2.receive_data,1) != HAL_OK);
		//{
			//huart2.RxState = HAL_UART_STATE_READY;
			//__HAL_UNLOCK(&huart2);
		//}
		//usart2.printf("Recv!\r\n");
		Res = usart2.receive_data;//��ȡ���յ�������
		if(RECV_FLAG==0)//���WIFI����͸��ģʽ����WIFI���ݴӵ��Կڴ�ӡ����
		{
			usart1.send_packet(&Res,1);
			//usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
			//usart2.USART_RX_STA++;
/*			
			if((usart2.USART_RX_STA&0x8000)==0)//����δ���
			{
				if(usart2.USART_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
					{
						usart2.USART_RX_STA=0;//���մ���,���¿�ʼ
					}else 
					{
						usart2.USART_RX_STA|=0x8000;	//��������� 
					}
				}
				else //��û�յ�0X0D
				{	
					if(Res==0x0d)
					{
						usart2.USART_RX_STA|=0x4000;
					}
					else
					{
						usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
						usart2.USART_RX_STA++;
						if(usart2.USART_RX_STA>(UART_BUFFER_SIZE-1))
						{
							usart2.USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	
						}							
					}		 
				}
			}*/
		}else
		{
			if((usart2.USART_RX_STA&0x8000)==0)//����δ��ɲŻ����������̣������������ˣ���Ҫ�ȴ����������꽫��־�������ܼ������ա�
			{
				if((usart2.USART_RX_STA&0x4000)==0)//��û���յ���0xAA
				{
					if(Res==0xAA) 
					{
						//usart2.printf("receive a AA\r\n");
						usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
						usart2.USART_RX_STA++;
						usart2.USART_RX_STA|=0x4000;	//bit14��־λ��1
					}
					else return;//û���յ�0xAA�������������Ҳ����0xAA�����˳�
				}
				else if((usart2.USART_RX_STA&0x2000)==0)//�Ѿ��յ�0XAA,��û���յ���0xCC
				{
					if(Res==0xCC)//�յ�0xCC
					{	
						//usart2.printf("receive CC\r\n");
						usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
						usart2.USART_RX_STA++;
						usart2.USART_RX_STA|=0x2000;	//bit13��־λ��1
					}
					else usart2.USART_RX_STA=0;//���մ���,���¿�ʼ
				}
				else//�����ǽ��հ�ͷ��������ݰ�
				{
					usart2.receive_buffer[usart2.USART_RX_STA&0X1FFF]=Res ;
					usart2.USART_RX_STA++;
					if((usart2.USART_RX_STA&0x1fff)==24)//����24�ֽ�
					{
						//usart6.printf("receive a packet\r\n");
						//usart6.send_packet((unsigned char*)usart1.receive_buffer, 24);
						Rcrc=crc16_ibm((uint8_t*)usart2.receive_buffer,22);//����CRCУ��ֵ
						if(((Rcrc&0xff)==usart2.receive_buffer[23]) && (((Rcrc>>8)&0xff)==usart2.receive_buffer[22]))
						{
							usart2.USART_RX_STA|=0x8000;	//��������� 
							//usart6.printf("CRCУ��ɹ�%x\r\n", Rcrc);
						}else
						{
							usart2.USART_RX_STA=0;//���մ���,���¿�ʼ
							//usart2.printf("CRCУ�����%x\r\n", Rcrc);
						}
					}
				}
			}
		}
	}
}

/*
 * Name               : my_printf4
 * Description        : ---
 * Author             : zh.
 * 
 * History
 * -------------------
 * Rev                : 0.00
 * Date               : 07/11/2019
 *t
 * create.
 * -------------------
 */
static int my_printf3(const char * fmt,...)
{
	__va_list arg_ptr;
	char buf[UART_BUFFER_SIZE];
	
	memset(buf,'\0',sizeof(buf));
	
	va_start(arg_ptr,fmt);
	vsprintf(buf,fmt,arg_ptr);
	va_end(arg_ptr);
	
	send_string_to_usart3(buf);
	
	return 0;
}
