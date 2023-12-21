#include "headfile.h"
#include "bal.h"
#include "motor.h"
#include "LQ_PID.h"
#include "encoder.h"
#include "electronic.h"
#include "element.h"

int16  Pulse_L=0, Pulse_R=0;
extern int8 Turn_flag;
extern float electro_error;
extern char gyroflag;
float Speed_L_Out=0, Speed_R_Out=0;
int16 Speed_Target_car = 0;
int16 Speed_Turn=0;
int16 L_Speed_Now_car=0, R_Speed_Now_car=0;
int16 L_Speed_Now_Error=0, R_Speed_Now_Error=0;
int16 L_Speed_Last_Error=0, R_Speed_Last_Error=0;
int16 Angle_Turn=0;

float Turn_OUT = 0;
int16 L_target=0, R_target=0;
float angle;                //实际的物理量

pid_param_t Turn_PID,Angle_PID,
L_Speed_PID,R_Speed_PID;
void All_PID_Init(void)
{ 
	Speed_Target_car=95;//速度赋值120
	
	PidInit(&L_Speed_PID);	
	PidInit(&R_Speed_PID);		
  PidInit(&Turn_PID);
	PidInit(&Angle_PID); 
	
  L_Speed_PID.kp = 10;				
  L_Speed_PID.ki = 0.01;												
  L_Speed_PID.kd = 0;
	
	R_Speed_PID.kp = 8;				
  R_Speed_PID.ki = 0.015;											
  R_Speed_PID.kd = 0;	
	
  Turn_PID.kp = 3.4;	//3.5		
  Turn_PID.ki = 0;
  Turn_PID.kd = 0.006;//0.001
	
	Angle_PID.kp = 0.4;//0.6		
  Angle_PID.ki = 0.011;//0
  Angle_PID.kd = 0;
}

void Encoder_cal(void)
{
		Pulse_L = encoder_get(EncoderL);		//编码器原始数据
		Pulse_L *= 2;
		Pulse_R = encoder_get(EncoderR);
	
		if(P53==0)
		{
			Pulse_R = -Pulse_R;
		}
		if(P35==1)
		{
			Pulse_L = -Pulse_L;
		}
}
/*************总控制***********/
void Bal_control(void)
{
	  if (gyroflag)
		{
		    imu660ra_get_gyro();
			angle=imu660ra_gyro_transition(imu660ra_gyro_z);
			Angle_Turn=PidIncCtrl(&Angle_PID, Turn_OUT+angle);
			gyroflag=0;
		}
		
		if(Turn_flag)			//电磁信号处理完成一次的标志位，5ms处理完成一次 执行一次转向pid计算
		{				
				Turn_OUT = PidLocCtrl(&Turn_PID, electro_error);   //闭环转向控制
			  Turn_flag=0;
		}
		velocity_control();	
}

/****************速度环***********/
void velocity_control(void)
{	
		L_Speed_Now_car=Pulse_L;
		R_Speed_Now_car=Pulse_R;
			
		//正常循迹
	  if(Speed_Turn<10) Speed_Turn=0;
		if(Speed_Turn>85)	Turn_PID.kp=3.6;
  	if(Speed_Turn<85&&Speed_Turn>10) Turn_PID.kp=3.4;
		L_target = Speed_Target_car + Angle_Turn;
		R_target = Speed_Target_car - Angle_Turn;
		
		L_Speed_Now_Error = L_target - L_Speed_Now_car;		
		R_Speed_Now_Error = R_target - R_Speed_Now_car;
		
		Speed_L_Out = PidIncCtrl(&L_Speed_PID, L_Speed_Now_Error);			//传递给速度环的误差为    期望速度-实际速度+/-转向环输出值
		Speed_R_Out = PidIncCtrl(&R_Speed_PID, R_Speed_Now_Error);			//左右轮分开pid		右轮加  左轮减
		
		ctimer_count_clean(EncoderL); 															         // 清空编码器计数
		ctimer_count_clean(EncoderR);                                        // 清空编码器计数
}
