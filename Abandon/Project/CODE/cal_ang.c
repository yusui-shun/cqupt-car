#include "headfile.h"
#include "all_init.h"
#include "MPU6050.h"
#include "encoder.h"

float gyroX, gyroY, gyroZ;
static const float dt = 8.0 / 1000;  // ���8ms
static const float ZERO_OFFSET_COUN=(1 / 8.0 * 1000);// 1/8=125��ÿ��    
 
static int g_GetZeroOffset = 0;
static float gyroX_offset = 0.0f, gyroY_offset = 0.0f, gyroZ_offset = 0.0f;

static float integralX = 0.0f, integralY = 0.0f, integralZ = 0.0f;

float ang_z;

void get_ang(void)
{
		MPU6050_Getdata1();		//���������6050��h�ļ� �����������ֱ��ʹ��icm�������ֵ
		gyroX=icm_gyro_x;
		gyroY=icm_gyro_y;
		gyroZ=icm_gyro_z;
    gyroX /= 16.384f; // �ҵ�MPU6050��ʼ���ġ�2000LSB���� (32768 / 2000) = 16.384f
		gyroY /= 16.384f;
		gyroZ /= 16.384f;
			// ���8msһ�β�����ͳ��125�Σ���1��ʱ��
		if (g_GetZeroOffset++ < ZERO_OFFSET_COUN)
		{
			gyroX_offset += gyroX * dt;  // ÿ��8%���֣��ۼƼ�Ȩ125��
			gyroY_offset += gyroY * dt;
			gyroZ_offset += gyroZ * dt;
		}
 
		// ��ȥ��ƫ
		gyroX -= gyroX_offset;
		gyroY -= gyroY_offset;
		gyroZ -= gyroZ_offset;
		
		if (g_GetZeroOffset > ZERO_OFFSET_COUN) // ͳ������ƫ��ʼ�ۼ�ƫ��
		{
			integralX += gyroX * dt;  // ÿ��8%Ȩ���ۼ�ƫת�Ƕ�
			integralY += gyroY * dt;
			integralZ += gyroZ * dt;
			// 360��һ��ѭ��
			if (integralX > 360)
				integralX -= 360;
			if (integralX < -360)
				integralX += 360;
			if (integralY > 360)
				integralY -= 360;
			if (integralY < -360)
				integralY += 360;
			if (integralZ > 360)
				integralZ -= 360;
			if (integralZ < -360)
				integralZ += 360;
		}
		ang_z=integralZ*6.18;	//*12�� ת90�ȶ�Ӧ106��
}