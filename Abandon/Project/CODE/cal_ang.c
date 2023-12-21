#include "headfile.h"
#include "all_init.h"
#include "MPU6050.h"
#include "encoder.h"

float gyroX, gyroY, gyroZ;
static const float dt = 8.0 / 1000;  // 间隔8ms
static const float ZERO_OFFSET_COUN=(1 / 8.0 * 1000);// 1/8=125次每秒    
 
static int g_GetZeroOffset = 0;
static float gyroX_offset = 0.0f, gyroY_offset = 0.0f, gyroZ_offset = 0.0f;

static float integralX = 0.0f, integralY = 0.0f, integralZ = 0.0f;

float ang_z;

void get_ang(void)
{
		MPU6050_Getdata1();		//上面包含了6050的h文件 所以这里可以直接使用icm这个变量值
		gyroX=icm_gyro_x;
		gyroY=icm_gyro_y;
		gyroZ=icm_gyro_z;
    gyroX /= 16.384f; // 我的MPU6050初始化的±2000LSB量程 (32768 / 2000) = 16.384f
		gyroY /= 16.384f;
		gyroZ /= 16.384f;
			// 间隔8ms一次采样，统计125次，共1秒时间
		if (g_GetZeroOffset++ < ZERO_OFFSET_COUN)
		{
			gyroX_offset += gyroX * dt;  // 每次8%积分，累计加权125次
			gyroY_offset += gyroY * dt;
			gyroZ_offset += gyroZ * dt;
		}
 
		// 除去零偏
		gyroX -= gyroX_offset;
		gyroY -= gyroY_offset;
		gyroZ -= gyroZ_offset;
		
		if (g_GetZeroOffset > ZERO_OFFSET_COUN) // 统计完零偏后开始累计偏角
		{
			integralX += gyroX * dt;  // 每次8%权重累计偏转角度
			integralY += gyroY * dt;
			integralZ += gyroZ * dt;
			// 360°一个循环
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
		ang_z=integralZ*6.18;	//*12后 转90度对应106度
}