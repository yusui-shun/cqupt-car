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


void MyI2C_W_SCL(uint8 BitValue)			//дSCL
{
	SCL1 = BitValue;
	Delay_us1(10);
}

void MyI2C_W_SDA(uint8 BitValue)			//дSDA
{
	SDA1 = BitValue;
	Delay_us1(10);
}

uint8 MyI2C_R_SDA(void)						//��SDA
{
	uint8 BitValue;
	BitValue = SDA1;
	Delay_us1(10);
	
	return BitValue;
}

void MyI2C_Init()     //��ʼ��
{
//	P3M0 |= 0x0c; //P32 �� P33Ϊ��©���
//	P3M1 |= 0x0c; 
	
    P4M0 |= 0x09;
	  P4M1 |= 0x09; 


}

void MyI2C_Start(void)//��ʼ
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)//ֹͣ
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8 Byte)//�����ֽ�
{
	int i;
	
	for (i=0;i<8;i++)
	{
		MyI2C_W_SDA(Byte & (0x80>>i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);	
	}

}

uint8 MyI2C_ReceiveByte(void)//��ȡ�ֽ�
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

void MyI2C_SendAck(uint8 AckBit)//����Ӧ��
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);	
}

uint8 MyI2C_ReceiveAck(void)//����Ӧ��
{
	uint8 AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);

	return AckBit;
}	
