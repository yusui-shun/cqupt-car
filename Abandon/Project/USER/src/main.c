/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
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
 * ϵͳƵ�ʣ��ɲ鿴board.h�е� FOSC �궨���޸ġ�
 * board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�����ϵͳƵ��Ϊ33.1776MHZ
 * ��board_init��,�Ѿ���P54��������Ϊ��λ
 * �����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����
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
	board_init();			// ��ʼ���Ĵ���,��ɾ���˾���롣
	All_init();
	//InductorNormal();
	while(key);
	pit_timer_ms(TIM_1,SPEED_IT_PERIOD);//�����������1ms
	// �˴���д�û�����(���磺�����ʼ�������)
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
		 // �˴���д��Ҫѭ��ִ�еĴ���
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