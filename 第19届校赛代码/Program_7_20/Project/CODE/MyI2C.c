//SCL: P32		SDA: P33
//SCL: P43		SDA: P40
//#define SCL1 P32
//#define SDA1 P33

#define SCL1 P43
#define SDA1 P40

#include "STC32Gxx.h"

#define uint8 unsigned char
	
void Delay_us1(int num)		//@33.1776MHz
{
	while(num--)
	{
		unsigned long i;

	i = 7UL;
	while (i) i--;
	}

}


void MyI2C_W_SCL(uint8 BitValue)			//写SCL
{
	SCL1 = BitValue;
	Delay_us1(10);
}

void MyI2C_W_SDA(uint8 BitValue)			//写SDA
{
	SDA1 = BitValue;
	Delay_us1(10);
}

uint8 MyI2C_R_SDA(void)						//读SDA
{
	uint8 BitValue;
	BitValue = SDA1;
	Delay_us1(10);
	
	return BitValue;
}

void MyI2C_Init()     //初始化
{
//	P3M0 |= 0x0c; //P32 和 P33为开漏输出
//	P3M1 |= 0x0c; 
	
    P4M0 |= 0x09;
	  P4M1 |= 0x09; 


}

void MyI2C_Start(void)//开始
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)//停止
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8 Byte)//发送字节
{
	int i;
	
	for (i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);	
	}

}

uint8 MyI2C_ReceiveByte(void)//读取字节
{
	uint8 Byte = 0x00, i;
	MyI2C_W_SDA(1);
	
	for (i = 0;i<8;i++)
	{
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA() == 1) { Byte |= (0x80>>i);}
		MyI2C_W_SCL(0);
	}

	return Byte;
}	

void MyI2C_SendAck(uint8 AckBit)//发送应答
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);	
}

uint8 MyI2C_ReceiveAck(void)//接收应答
{
	uint8 AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);

	return AckBit;
}	
