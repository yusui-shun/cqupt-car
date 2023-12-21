#include "headfile.h"
#include "motor.h"
#include "encoder.h"
#include "bal.h"
#include "electronic.h"
extern int16  Pulse_L, Pulse_R;
extern float Speed_L_Out,Speed_R_Out;
extern int16 LnowADC[];
extern float Turn_OUT;
extern float electro_error;
extern int16 Speed_Turn;
extern float angle;
extern int16 Angle_Turn;
extern int16 imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;                 // 三轴陀螺仪数据      gyro (陀螺仪)
extern int16 imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;                    // 三轴加速度计数据     acc (accelerometer 加速度计)
void All_init(void){
    Motor_Init();
    Encoder_init();
    All_PID_Init();
    ADC_6_road_init();
    lcd_init_simspi();
		imu660ra_init();
  	wireless_uart_init();
	  P3M0 |= 0x40; P3M1 &= ~0x40; 
		P36 = 1;
}

void Tft_show(void){//屏幕显示函数，显示都写在这里面
		lcd_showstr_simspi(0,0,"zys666");
		lcd_showstr_simspi(0,1,"left");
    lcd_showint16_simspi(0,2,Pulse_L);               
										//左电机编码器显示
		lcd_showstr_simspi(0,3,"right");
    lcd_showint16_simspi(0,4,Pulse_R);               
										//右电机编码器显示
//		lcd_showstr_simspi(0,5,"left_right");
//		lcd_showint16_simspi(0,6,Speed_L_Out);  
//		lcd_showint16_simspi(0,7,Speed_R_Out);  
										//左右电机输出显示
		lcd_showint16_simspi(0,5,electro_error);
		lcd_showint16_simspi(0,6,LnowADC[0]);
		lcd_showint16_simspi(0,7,LnowADC[5]);
                    //电感显示
//		lcd_showint16_simspi(0,5,imu660ra_gyro_x);             
//		lcd_showint16_simspi(0,6,imu660ra_gyro_y);             
//		lcd_showint16_simspi(0,7,imu660ra_gyro_z);                
//		lcd_showint16_simspi(0,8,imu660ra_acc_x);                
//		lcd_showint16_simspi(0,9,imu660ra_acc_y);                
//		lcd_showint16_simspi(0,10,imu660ra_acc_z);                
                    //陀螺仪数值显示
}
void Tft_Printf(void){//波形打印函数
		//printf("%d,%d,%d\n",Pulse_L,Pulse_R,63);//输出左右脉冲
	printf("%d,%d,%d,%.2f,%d,%.2f,%.2f\n",120,Pulse_L,Pulse_R,angle,Angle_Turn,Speed_L_Out,Speed_R_Out);
	
}