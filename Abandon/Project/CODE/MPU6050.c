#include "MyI2C.H"
#include "MPU6050_Reg.h"
#include "MPU6050.h"
#define MPU6050_ADDRESS          0xD0

int16 icm_gyro_x,icm_gyro_y,icm_gyro_z;
int16 icm_acc_x,icm_acc_y,icm_acc_z;

void MPU6050_WriteReg(uint8 RegAddress, uint8 Data)
{
	MyI2C_Start();
	
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	
	MyI2C_Stop();
}

uint8 MPU6050_ReadReg(uint8 RegAddress)
{
	uint8 Data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);	//发送读指令
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	
	MyI2C_SendAck(1);
	MyI2C_Stop();
	
	return Data;
}

void MPU6050_Init1(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); //解除睡眠，陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00); // 6轴都不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);    // 采样分频10
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);   //滤波
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);             //0x18   0-7 8位 只看第3和低4位 十进制0-3配置量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

void MPU6050_GetData(int16 *AccX, int16 *AccY, int16 *AccZ,
										int16 *GyroX, int16 *GyroY, int16 *GyroZ)
{
	uint8 DataH, DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8) | DataL;
}

void MPU6050_Getdata1(void)
{
	MPU6050_GetData(&icm_acc_x,&icm_acc_y,&icm_acc_z,&icm_gyro_x,&icm_gyro_y,&icm_gyro_z);
}