#include "headfile.h"
#include "encoder.h"
/*extern int16 EncoderGetSpeed;
int16 p=0;

void encoder_init(void)
{
	ctimer_count_init(CTIM3_P04);
	//定时器1初始化 定时进中断 读取速度值
	TM1PS = 350-1;     //35m/350 = 10e5   				35 000 000  35000   1000
	TMOD = 0x00; //模式 0
	TL1 = 0xEF;    				//55535  记10000个数   //0.1s
	TH1 = 0xD8;
	TR1 = 1; //启动定时器
	ET1 = 1; //使能定时器中断
	EA = 1; 
}

int16 encoder_get(CTIMN_enum pin)
{
	uint16 t;
	t=ctimer_count_read(pin);
	ctimer_count_clean(pin);
	return t;
}

void TM1_Isr() interrupt 3   //定时器1进中断读取速度
{
	TL1 = 0xEF;    
	TH1 = 0xD8;
	EncoderGetSpeed = encoder_get();
//	pid_motor.ActualValue = (uint16) (PWMA_CNTRH << 8) | PWMA_CNTRL; //获取当前编码器的值
//	Exp_Val = pid_motor.ActualValue + PID_Control_Inc(&pid_motor);   //期望值（区分于目标值）										
	//pwm.....(Exp_Val); //期望值转化成占空比 
//	PWMB_CNTRH = 0; //清零编码器计数器值
//	PWMB_CNTRL = 0;	
} */