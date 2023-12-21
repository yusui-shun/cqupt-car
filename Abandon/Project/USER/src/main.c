/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-12-18
 ********************************************************************************************************************/

#include "headfile.h"
#include "all_init.h"
#include "bal.h"
#include "element.h"
#include "motor.h"
#include "LQ_PID.h"


/*
 * 系统频率，可查看board.h中的 FOSC 宏定义修改。
 * board.h文件中FOSC的值设置为0,则程序自动设置系统频率为33.1776MHZ
 * 在board_init中,已经将P54引脚设置为复位
 * 如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可
 */
 
 sbit key = P1^7;
extern float electro_error; 
extern int16 LnowADC[6];
extern int16 MagneticField;
extern int8  ring_stop;
extern float Turn_OUT;
extern float Speed_L_Out,Speed_R_Out;
extern int16 L_Speed_Now_Error;
 
extern int16 global_L_Speed_Now_car,global_R_Speed_Now_car;
extern int16 L_Speed_Now_Error,R_Speed_Now_Error;
extern uint16  Speed_Target_car;
extern float L_target,R_target;
extern int16  Pulse_L,Pulse_R;
extern int8 Turn_flag;
extern int8 start_judge;

extern pid_param_t Turn_PID,
L_Speed_PID,R_Speed_PID;

void main()
{
	board_init();			// 初始化寄存器,勿删除此句代码。
	All_init();
	//InductorNormal();
	while(key);
	pit_timer_ms(TIM_1,SPEED_IT_PERIOD);//电机控制周期1ms
	// 此处编写用户代码(例如：外设初始化代码等)
	out_garage();
    while(1)
	{
		
//		if(key==0)
//	{
//		while(key==0);
//		pwm=pwm+100;
//	}
//		Speed_L_Out = 0;
//		Speed_R_Out	= 0;
//		Motor_SpeedSet(Speed_L_Out+pwm,Speed_R_Out+pwm);
		lcd_showfloat_simspi(0,0,Speed_L_Out,4,1);
		lcd_showfloat_simspi(0,1,Speed_R_Out,4,1);
		lcd_showfloat_simspi(0,2,L_Speed_PID.out,4,1);
		lcd_showfloat_simspi(0,3,R_Speed_PID.out,4,1);
		 // 此处编写需要循环执行的代码
		//Tft_show();
		//lcd_showfloat_simspi(0,0,electro_error,3,1);
		//lcd_showint16_simspi(0,1,MagneticField);
//		lcd_showint16_simspi(0,2,LnowADC[0]);
		//lcd_showint16_simspi(0,3,LnowADC[1]);
	//	lcd_showint16_simspi(0,4,LnowADC[2]);
	//	lcd_showint16_simspi(0,5,LnowADC[4]);
	//	lcd_showint16_simspi(0,6,LnowADC[5]);
		
	//printf("%d,%d,%f,%f,%f,%f,%f,%f,%d,%d,%d\n",global_L_Speed_Now_car,global_R_Speed_Now_car,Speed_L_Out,Speed_R_Out,L_target,
	//R_target,electro_error,Turn_OUT,start_judge,L_Speed_Now_Error,R_Speed_Now_Error);

}
}