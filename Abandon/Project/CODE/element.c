#include "element.h"
#include "headfile.h"
#include "bal.h"
#include "electronic.h"
#include "math.h"



#define max_ele 650
#define min_ele 200

int8 flag_garage=0;//霍尔标志位
int8 start_judge=0;
bit flag_electronic=0;
int16 flag_element_L=0,flag_element_R=0;
int16 flag_stop_ring=0;
int8 stop_garage=0;
int16 time_ring=0;
bit outRing_flag = 0;
int8 bal_stop=0;
int8 after_ring_in_garage=0;
extern float electro_error;
float	road_L=0,road_R=0,road=0;		//圆环记录距离
extern int16 AddSpeed;
extern int16 LnowADC[6];
extern int16 MagneticField;
extern flag_stop;
extern float Speed_L_Out,Speed_R_Out;
extern float Turn_OUT;
extern int16 L_Speed_Now_Error,R_Speed_Now_Error;

extern pid_param_t Turn_PID,
L_Speed_PID,R_Speed_PID;

void Judge_Game(void)
{	
//	out_garage();
	
	if(start_judge)
	 {
//		 	 if(Turn_PID.kp<Turn_kp) 
//			 {
//					Turn_PID.kp += 0.001;
//			 }
	  Bal_control();
		 
		go_4_ring();
		 
		if(MagneticField < 100)
		{
			flag_stop = 1;
			Speed_R_Out = 0;  //电机给PWM波进行控制
			Speed_L_Out = 0;
			
//			L_Speed_Now_Error = 0;		
//		  R_Speed_Now_Error = 0;
		}
		
		if(stop_garage)
		{
			Speed_L_Out=0;
			Speed_R_Out=0;
			
//			L_Speed_Now_Error = 0;		
//		  R_Speed_Now_Error = 0;
		}
		
		Motor_SpeedSet(Speed_L_Out,Speed_R_Out);
	 }
	 
		
	if(LnowADC[2]>400 && fabs(electro_error)>30)
	{
		P36 = 0;
	}
	else
	{
		P36 = 1;
	}

}



void in_garage(void)
{
	if(after_ring_in_garage)
	{
		if(!P45)
		{
			stop_garage=1;
		}
	}
}


void go_4_ring(void)
	{
		if(time_ring>0)
		{
			outRing_flag = 1;
			time_ring--;
		}
	if(LnowADC[1]>500&&MagneticField>1200&&outRing_flag==0)
	{
		
		after_ring_in_garage=1;
				time_ring=650;
		
	}
	if(time_ring)
	{
		//P36 = 0;
		Speed_R_Out=0;//16 400 1900 满电压  // 
		Speed_L_Out=2400;
	}

}
//	if (flag_stop_ring)
//		if( LnowADC[1]>400 )
//		{

//			Motor_SpeedSet(2000, 500);
//		}
//		else
//		{
//			Speed_R_Out=0;//电机给PWM波进行控制
//				Speed_L_Out=0;
//				P36 = 1;
//		}

void out_garage(void)
{
//	static int8 P45_flag=0;
//	if(!P45)
//	{
//	Speed_R_Out=1200;
//	Speed_L_Out=1300;
//	}
//	else if(P45){
//		P45_flag=1;
//	}
//	if(electro_error<10&&P45_flag){
//			Speed_R_Out=1500;
//			Speed_L_Out=0;
//	}
//	if(LnowADC[1]>100&&P45_flag)
//		{
//						Speed_R_Out=0;
//			Speed_L_Out=0;
//				start_judge=1;
//		}
	
	while (!P45)
	{
		Motor_SpeedSet(1250,1200);
	}
	
	Motor_SpeedSet(0,0);
	delay_ms(500);
	
	Motor_SpeedSet(0,3000);
	delay_ms(400);
	
	start_judge = 1;
}

void go_ring(void)
{
	if(flag_element_L>0){
		flag_element_L--;
	}
	if(flag_element_R>0){
		flag_element_R--;
	}
  if( ( (LnowADC[0] > max_ele && LnowADC[5] > min_ele)  ||  (LnowADC[0] > 450 && LnowADC[5] > 450)   )  && MagneticField > 1300 )   //一定遇到“元素”了  并且该元素是 期望让车 向左拐
		{		
			flag_element_L = 1000;
			flag_stop_ring=1;
	   	P36 = 0;
		}
		
//		if( ( (LnowADC[5] > max_ele && LnowADC[0] > min_ele) || (LnowADC[0] > 500 && LnowADC[5] > 500) )  && MagneticField > 1100 )   //期望让车 向右拐
//		{		
//				flag_element_R = 1000;
//				P36 = 1;
//		}
		
		if( ( (LnowADC[0] - LnowADC[5]) < 400 && (LnowADC[0] - LnowADC[5]) > -400 ) || ( LnowADC[0]>700 && LnowADC[5] < 60 ) || 	
											( LnowADC[5]>max_ele && LnowADC[0] < 60 )		)				//无元素 期望小车正常控制行驶	不用外加干扰
		{
			P36 = 1;
		}
		
		if(flag_element_L>0&&flag_stop_ring)		//控制小车向左拐，直到离开元素 
		{
				// Speed_R_Out-=500;
		}	
		if(flag_element_R>0)
		{
				// Speed_L_Out-=500;
		}	
		
}

