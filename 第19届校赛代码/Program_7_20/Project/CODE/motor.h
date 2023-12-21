
/*
 * motor.h
 *
 *  Created on: 2023��3��12��
 *      Author: yu
 */
#include "headfile.h"
#ifndef CODE_Motor_H_
#define CODE_Motor_H_

#define MotorB_N    PWMA_CH3P_P64//���ַ�ת
#define MotorA_N    PWMA_CH4P_P66//������ת

#define MotorA_P    PWMA_CH2P_P62//���ַ�ת
#define MotorB_P    PWMA_CH1P_P60//������ת

#define MotorFre    17000				//pwmĬ��Ƶ��17k

#define difference  //��е���
#define Death_Duty_L 0 //����������ѹ
#define Death_Duty_R 0 //�ҵ��������ѹ

#define MAXDUTY 3000

#define Encoder_left CTIM0_P34
#define Encoder_right CTIM3_P04

#define Dir_left P50
#define Dir_right P51

void Encoder_init(void);//��������ʼ��
int16 encoder_get(CTIMN_enum pin);
void Motor_Init(void);//�����ʼ��
void Motor_SpeedSet(int16 Duty_L,int16 Duty_R);//�����PWM�����п���
void Duty_Limit(int16 Duty);

#endif /* CODE_MOTOR_H_ */
