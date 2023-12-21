#include "headfile.h"


#ifndef CODE_BAL_H_
#define CODE_BAl_H_

#define EncoderL CTIM0_P34
#define EncoderR CTIM3_P04

void Encoder_cal(void);
void Bal_control(void);
void velocity_control(void);
float turn_control(float  Speed_Turn );
void All_PID_Init(void);
float angle_calc(float angle_m, float gyro_m);

#endif