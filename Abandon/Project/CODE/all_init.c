#include "headfile.h"
#include "motor.h"
#include "encoder.h"
#include "bal.h"
#include "electronic.h"

void All_init(void){
    Motor_Init();
    Encoder_init();
    All_PID_Init();
    ADC_6_road_init();
    lcd_init_simspi();
//		imu660ra_init();
	    P3M0 |= 0x40; P3M1 &= ~0x40; 
		P36 = 1;
}

void Tft_show(void){//屏幕显示函数，显示都写在这里面
		lcd_showstr(0,0,"zys666");
                    //左电机编码器显示
                    //右电机编码器显示
                    //电感显示
                    //陀螺仪数值显示

}