#include "headfile.h"


#ifndef CODE_BAL_H_
#define CODE_BAl_H_

#define EncoderL CTIM0_P34
#define EncoderR CTIM3_P04

#define L_Speed_kp 450      // 450
#define L_Speed_ki 0.02     // 0.02

#define R_Speed_kp 350      // 350
#define R_Speed_ki 0.05     // 0.05

#define Turn_kp 0.1  

#define Speed_Target 17 * SPEED_IT_PERIOD  //15 16

#define SPEED_IT_PERIOD 1			//定时器1  中断时间 1ms 

void Bal_control(void);
void velocity_control(void);
float turn_control(float  Speed_Turn );
void All_PID_Init(void);

#endif