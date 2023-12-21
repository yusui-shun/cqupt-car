
/*
 * motor.h
 *
 *  Created on: 2023年3月12日
 *      Author: yu
 */
#include "headfile.h"
#ifndef CODE_Motor_H_
#define CODE_Motor_H_

#define MotorB_N    PWMA_CH3P_P64//左轮反转
#define MotorA_N    PWMA_CH4P_P66//左轮正转

#define MotorA_P    PWMA_CH2P_P62//右轮反转
#define MotorB_P    PWMA_CH1P_P60//右轮正转

#define MotorFre    17000				//pwm默认频率17k

#define difference  //机械误差
#define Death_Duty_L 0 //左电机死区电压
#define Death_Duty_R 0 //右电机死区电压

#define MAXDUTY 3000

#define Encoder_left CTIM0_P34
#define Encoder_right CTIM3_P04

#define Dir_left P50
#define Dir_right P51

void Encoder_init(void);//编码器初始化
int16 encoder_get(CTIMN_enum pin);
void Motor_Init(void);//电机初始化
void Motor_SpeedSet(int16 Duty_L,int16 Duty_R);//电机给PWM波进行控制
void Duty_Limit(int16 Duty);

#endif /* CODE_MOTOR_H_ */
