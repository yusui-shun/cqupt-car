#ifndef __MPU6050_H
#define __MPU6050_H

extern int16 icm_gyro_x, icm_gyro_y, icm_gyro_z;
extern int16 icm_acc_x, icm_acc_y, icm_acc_z;

void MPU6050_WriteReg(uint8 RegAddress, uint8 Data);
uint8 MPU6050_ReadReg(uint8 RegAddress);
void MPU6050_Init1(void);
void MPU6050_GetData(int16 *AccX, int16 *AccY, int16 *AccZ,
										int16 *GyroX, int16 *GyroY, int16 *GyroZ);
void MPU6050_Getdata1(void);
	
#endif
