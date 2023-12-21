#ifndef __MYI2C_H
#define __MYI2C_H

#include "common.h"

void MyI2C_Init(void);    //初始化
void MyI2C_Start(void);//开始
void MyI2C_Stop(void);//停止
void MyI2C_SendByte(uint8 Byte);//发送字节
uint8 MyI2C_ReceiveByte(void);//读取字节
void MyI2C_SendAck(uint8 AckBit);//发送应答
uint8 MyI2C_ReceiveAck(void);//接收应答

#endif
