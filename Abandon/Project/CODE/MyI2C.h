#ifndef __MYI2C_H
#define __MYI2C_H

#include "common.h"

void MyI2C_Init(void);    //��ʼ��
void MyI2C_Start(void);//��ʼ
void MyI2C_Stop(void);//ֹͣ
void MyI2C_SendByte(uint8 Byte);//�����ֽ�
uint8 MyI2C_ReceiveByte(void);//��ȡ�ֽ�
void MyI2C_SendAck(uint8 AckBit);//����Ӧ��
uint8 MyI2C_ReceiveAck(void);//����Ӧ��

#endif
