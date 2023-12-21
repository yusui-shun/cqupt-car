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
extern int16 time_ring;
float Speed_L_Out=0, Speed_R_Out=0;

uint16 Speed_Target_car = 0;
int16 AddSpeed=0;
// int16 Pulse_L_last=0,Pulse_R_last=0;



int16 global_L_Speed_Now_car=0,global_R_Speed_Now_car=0;

//速度环参数
int16 Basic_L_Speed=0,Basic_R_Speed=0;
int16 L_Speed_Now_car=0,R_Speed_Now_car=0;
int16 L_Speed_Now_Error=0,R_Speed_Now_Error=0;
int16 L_Speed_Last_Error=0, R_Speed_Last_Error=0;

float global_pid_kp_out=0, global_pid_ki_out=0;

pid_param_t Turn_PID,
L_Speed_PID,R_Speed_PID;


float Turn_OUT=0;

float Turn_OUT_Error=0;
float L_target=0,R_target=0;

float Turn_K1 = 0, Turn_K2 = 0;   // 4, 2

uint16 Brake_CNT = 0;
uint16 Brake_Flag = 0;

void All_PID_Init(void)
{  		
  PidInit(&L_Speed_PID);   
	PidInit(&R_Speed_PID);		
  PidInit(&Turn_PID);
	
	/*
	1 在速度为4的时候，200 1 150 1 比较慢
	2 在速度为8的时候，
	3 在速度为12的时候，校赛速度差不多  
  4 
	
	*/	
	//速度赋值


  L_Speed_PID.kp = L_Speed_kp;				//对应右轮参数`		//500
  L_Speed_PID.ki = L_Speed_ki;												//0.02
  L_Speed_PID.kd = 0;
	
	R_Speed_PID.kp = R_Speed_kp;				//对应左轮参数		//300
  R_Speed_PID.ki = R_Speed_ki;											//0.05
  R_Speed_PID.kd = 0;	
	
  Turn_PID.kp = Turn_kp;			//1  0.02
  Turn_PID.ki = 0;
  Turn_PID.kd = 0;
	
	Speed_Target_car = Speed_Target;
}

/*************总控制***********/
void Bal_control(void)
{
		if(Turn_flag)			//电磁信号处理完成一次的标志位，5ms处理完成一次 执行一次转向pid计算
		{				
				Turn_OUT = PidIncCtrl(&Turn_PID, electro_error); //转向控制
				Turn_flag = 0;
		}
		
//		Speed_Target_car = Speed_Target;
		
		if(electro_error<-85 || electro_error>85)
		{
		//	P36 = 1;
			Brake_Flag = 1;
		}
		else
		{
			Brake_CNT++;
			
			if(Brake_CNT >= 10)
			{
				Brake_Flag = 0;
		//		P36 = 1;
				Brake_CNT = 0;
			}
		}
		
		
		if(Brake_Flag == 1 || time_ring > 0 )
		{
			Speed_Target_car = Speed_Target - 1;
		}
		else
		{
			Speed_Target_car = Speed_Target;
		}
		
			
//		if(electro_error<-90)
//		{
////				Speed_L_Out+=Turn_K1*electro_error;
//			P36 = 0;
//		}
//		else if(electro_error>90){
////					Speed_R_Out-=Turn_K2*electro_error;
//			P36 = 0;
//		}
//		else
//		{
//			P36 = 1;
//		}
		
		velocity_control();		//1ms编码器执行一次 完成一次速度环计算
		
//		if(electro_error<-98||electro_error>98)
//		{
//			 Speed_L_Out-=Turn_K1*electro_error;
//			 Speed_R_Out-=Turn_K2*electro_error;
//		}

}

/****************速度环***********/
void velocity_control(void)
{
		Pulse_L = encoder_get(EncoderL);		//编码器原始数据
		Pulse_R = encoder_get(EncoderR);
		
		if(P53==0)
		{
			Pulse_L = -Pulse_L;
		}
		
		if(P35==1)
		{
			Pulse_R = -Pulse_R;
		}
		
		L_Speed_Now_car=Pulse_L;
		R_Speed_Now_car=Pulse_R;
		
		global_L_Speed_Now_car = L_Speed_Now_car;
		global_R_Speed_Now_car = R_Speed_Now_car;
		
		if (Turn_OUT >=0)
		{
			L_target = Speed_Target_car;
			R_target = 2*Speed_Target_car - 2*Turn_OUT;
		}
		else
		{
			L_target = Speed_Target_car + Turn_OUT;
			R_target = 2*Speed_Target_car;
		}
		
		L_Speed_Now_Error = L_target - L_Speed_Now_car;		
		R_Speed_Now_Error = R_target - R_Speed_Now_car;
		
		
		if(L_Speed_Now_Error < 0)
		{
	  	L_Speed_PID.kp = 1.15 * L_Speed_kp;
			L_Speed_PID.ki = L_Speed_ki;
		}
		else
		{
			L_Speed_PID.kp = L_Speed_kp;
			L_Speed_PID.ki = L_Speed_ki;
		}
		
		if(R_Speed_Now_Error < 0)
		{
			R_Speed_PID.kp = 1.15 * R_Speed_kp;
			R_Speed_PID.ki = R_Speed_ki;
		}
		else
		{
			R_Speed_PID.kp = R_Speed_kp;
			R_Speed_PID.ki = R_Speed_ki;
		}
		
		
//	Speed_L_Out += L_Speed_PID.kp *(L_Speed_Now_Error - L_Speed_Last_Error) + L_Speed_PID.ki * L_Speed_Now_Error;
//	Speed_R_Out += R_Speed_PID.kp *(R_Speed_Now_Error - R_Speed_Last_Error) + R_Speed_PID.ki * R_Speed_Now_Error;
		
		
		Speed_L_Out = PidIncCtrl(&L_Speed_PID, L_Speed_Now_Error);			//传递给速度环的误差为    期望速度-实际速度+/-转向环输出值
		Speed_R_Out = PidIncCtrl(&R_Speed_PID, R_Speed_Now_Error);			//左右轮分开pid		右轮加  左轮减
		
		
		if(Speed_L_Out <-MAXDUTY)
		{
			Speed_L_Out = -MAXDUTY;
			L_Speed_PID.out = -MAXDUTY;
		}
		else if(Speed_L_Out >MAXDUTY)
		{
			Speed_L_Out = MAXDUTY;
			L_Speed_PID.out = MAXDUTY;
		}
		
		
		if(Speed_R_Out < -MAXDUTY)
		{
			Speed_R_Out = -MAXDUTY;
			R_Speed_PID.out = -MAXDUTY;
		}
		else if(Speed_R_Out > MAXDUTY)
		{
			Speed_R_Out = MAXDUTY;
			R_Speed_PID.out = MAXDUTY;
		}
		
//	L_Speed_Last_Error = L_Speed_Now_Error;		
//	R_Speed_Last_Error = R_Speed_Now_Error;
		
		ctimer_count_clean(EncoderL); 															         // 清空编码器计数
		ctimer_count_clean(EncoderR);                                        // 清空编码器计数
}
